#include "simple_pwm.h"
#include "boards.h"
#include "math.h"

uint16_t sinus_pulse_1000ms[50];
uint16_t sinus_pulse_500ms[25];
uint16_t fade_in_1000ms[50];
uint16_t fade_out_1000ms[50];

typedef struct
{
    bool constant;
    uint16_t *data_ptr;
    float    *data_ptr_float;
    uint32_t  data_length;
    uint32_t  data_index;
    uint32_t  loop_counter;
}simple_pwm_channel_config_t;

#define SEQ_VALUE_BY_CHANNEL(channel) (*(&m_simple_pwm_seq_values.channel_0 + (channel)))

static nrf_drv_pwm_t m_pwm0 = NRF_DRV_PWM_INSTANCE(0);

static simple_pwm_channel_config_t m_channel_config[SIMPLE_PWM_CHANNEL_NUM];

static nrf_pwm_values_individual_t m_simple_pwm_seq_values;
static nrf_pwm_sequence_t const    m_simple_pwm_seq =
{
    .values.p_individual = &m_simple_pwm_seq_values,
    .length              = NRF_PWM_VALUES_LENGTH(m_simple_pwm_seq_values),
    .repeats             = 0,
    .end_delay           = 0
};

static void simple_pwm_handler(nrf_drv_pwm_evt_type_t event_type)
{
    if (event_type == NRF_DRV_PWM_EVT_FINISHED)
    {
        for(int i = 0; i < SIMPLE_PWM_CHANNEL_NUM; i++)
        {
            if(!m_channel_config[i].constant)
            {
                if(m_channel_config[i].data_ptr != 0)
                {
                    SEQ_VALUE_BY_CHANNEL(i) = m_channel_config[i].data_ptr[m_channel_config[i].data_index++];
                }
                else
                {
                    SEQ_VALUE_BY_CHANNEL(i) = (uint32_t)(m_channel_config[i].data_ptr_float[m_channel_config[i].data_index++] * (float)SIMPLE_PWM_MAX_VALUE);
                }
                if(m_channel_config[i].data_index >= m_channel_config[i].data_length)
                {
                   if(m_channel_config[i].loop_counter == 0)
                   {
                       m_channel_config[i].data_index = 0;
                   }
                   else
                   {
                       m_channel_config[i].loop_counter--;
                       m_channel_config[i].data_index = 0;
                       if(m_channel_config[i].loop_counter == 0)
                       {
                            m_channel_config[i].constant = true;   
                       }
                   }
                }
            }            
        }        
    }
}

static void calculate_preset_buffers(void)
{
    for(int i = 0; i < 50; i++)
    {
        sinus_pulse_1000ms[i] = (uint16_t)((1.0f-cosf((float)(i+1) / 50.0f * 2 * 3.141592f)/2.0f-0.5f) * (float)SIMPLE_PWM_MAX_VALUE);
        sinus_pulse_500ms[i / 2] = sinus_pulse_1000ms[i];
    }
    
    for(int i = 0; i < 50; i++)
    {
       fade_in_1000ms[i] = SIMPLE_PWM_MAX_VALUE * (i + 1) / 50;
       fade_out_1000ms[i] = SIMPLE_PWM_MAX_VALUE * (49 - i) / 50;
    }
}
                                
void pwm_init(uint8_t *pin_list, uint32_t pin_num)
{
    if(pin_num >= 1 && pin_num <= SIMPLE_PWM_CHANNEL_NUM)
    {
        nrf_drv_pwm_config_t config0 =
        {
            .irq_priority = APP_IRQ_PRIORITY_LOWEST,
            .base_clock   = NRF_PWM_CLK_1MHz,
            .count_mode   = NRF_PWM_MODE_UP,
            .top_value    = SIMPLE_PWM_MAX_VALUE,
            .load_mode    = NRF_PWM_LOAD_INDIVIDUAL,
            .step_mode    = NRF_PWM_STEP_AUTO
        };
        for(int i = 0; i < NRF_PWM_CHANNEL_COUNT; i++)
        {
            config0.output_pins[i] = (i < pin_num) ? pin_list[i] : NRF_DRV_PWM_PIN_NOT_USED;
        }
        APP_ERROR_CHECK(nrf_drv_pwm_init(&m_pwm0, &config0, simple_pwm_handler));

        for(int i = 0; i < SIMPLE_PWM_CHANNEL_NUM; i++)
        {
            m_channel_config[i].constant = true;
            m_channel_config[i].loop_counter = 0;
            SEQ_VALUE_BY_CHANNEL(i) = 0;
        }

        (void)nrf_drv_pwm_simple_playback(&m_pwm0, &m_simple_pwm_seq, 1,
                                          NRF_DRV_PWM_FLAG_LOOP);
        calculate_preset_buffers();
    }
}

void pwm_set_constant(uint32_t ch_index, uint32_t duty_cycle)
{
    if(ch_index < SIMPLE_PWM_CHANNEL_NUM)
    {
        SEQ_VALUE_BY_CHANNEL(ch_index) = duty_cycle;
        m_channel_config[ch_index].constant = true;
    }
}

void pwm_set_constant_f(uint32_t ch_index, float duty_cycle)
{
    if(ch_index < SIMPLE_PWM_CHANNEL_NUM)
    {
        SEQ_VALUE_BY_CHANNEL(ch_index) = (uint32_t)(duty_cycle * SIMPLE_PWM_MAX_VALUE);
        m_channel_config[ch_index].constant = true;
    }
}

void pwm_set_loop(uint32_t ch_index, uint16_t *buffer, uint32_t length, uint32_t loop_num)
{
    if(ch_index < SIMPLE_PWM_CHANNEL_NUM)
    {
        m_channel_config[ch_index].constant       = false;
        m_channel_config[ch_index].data_ptr       = buffer;
        m_channel_config[ch_index].data_ptr_float = 0;
        m_channel_config[ch_index].data_length    = length;
        m_channel_config[ch_index].loop_counter   = loop_num;
    }
}

void pwm_set_loop_f(uint32_t ch_index, float *buffer, uint32_t length, uint32_t loop_num)
{
    if(ch_index < SIMPLE_PWM_CHANNEL_NUM)
    {
        m_channel_config[ch_index].constant       = false;
        m_channel_config[ch_index].data_ptr       = 0;
        m_channel_config[ch_index].data_ptr_float = buffer;
        m_channel_config[ch_index].data_length    = length;
        m_channel_config[ch_index].loop_counter   = loop_num;
    }
}
