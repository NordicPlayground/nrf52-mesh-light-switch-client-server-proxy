# Introduction to nRF5 SDK for Mesh

The nRF5 SDK for Mesh is Nordic Semiconductor's implementation of the Bluetooth Mesh. It allows
applications to utilize the features provided by the Bluetooth Mesh when running on Nordic's
nRF5 Series chips.

Make sure to check the @subpage md_RELEASE_NOTES for the current release, and the
@subpage md_MIGRATION_GUIDE for migration between releases.

Refer to @subpage md_COPYING for the Copyright Notice.

> **Important:**
>
> The nRF5 SDK for Mesh now **requires** the
> <a href="http://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/" target="_blank">nRF5 SDK 15.0.0</a>
> to compile. Please refer to @ref md_doc_getting_started_how_to_build for more information.
>
> In an application using nRF5 SDK for Mesh, interrupt priorities need to be considered carefully,
> see @ref md_doc_getting_started_mesh_interrupt_priorities.

## Scope
This hands-on exercise is meant to give a solid introduction to the nRF5 Mesh SDK, as well as the nRF Mesh mobile provisioning application. In addition, the exercise will show how you can integrate elements from the nRF5 SDK into the Mesh SDK example.

## Requirements
This mesh example code has been tested with the nRF52840 DK, but should also work with the nRF52832 DK.
- multiple nRF52840 DK (at least two, preferably more)
- PC running either Windows, MacOS or Linux
- 1x smartphone (iOS or Android)
- 1x micro USB cable
- [Segger Embedded Studio](https://www.segger.com/products/development-tools/embedded-studio/)
- latest version of the [J-Link Software & Documentation Pack](https://www.segger.com/downloads/jlink#)
- [nRF5_SDK_v15.0.0](https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/)
- nRF Mesh mobile application (download from App Store or Google Play)


## How To Get Started
Open up the *Mesh Hands-on iOS_October2018.pdf* or *Mesh Hands-on Android_october2018.pdf*, depending on whether you want to run [nRF Mesh](https://www.nordicsemi.com/eng/Products/Nordic-mobile-Apps/nRF-Mesh) on iOS or Android.

## Documentation

Refer to the following guides for understanding basic concepts of Bluetooth mesh and architecture of
the Nordic nRF5 SDK for Mesh:
  - @subpage md_doc_getting_started_mesh_quick_start
  - @subpage md_doc_introduction_basic_concepts
  - @subpage md_doc_introduction_basic_architecture
  
## Disclaimer
- The examples are not extensively tested, are only meant for tutorial purposes & should hopefully facilitate a better understanding of the Nordic Mesh SDK.
- NO WARRANTY of ANY KIND is provided.
