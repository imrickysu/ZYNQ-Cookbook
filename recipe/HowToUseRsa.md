# How to Use RSA Authentication in ZYNQ #

ZYNQ security keys are stored in two different parts: AES keys in PL and RSA keys in PS. This artical is mainly for RSA authentication in PS.

## References ##
- UG1025
- Xapp1175
- UG821 Appx.A
- UG585 Ch32 and Ch6

## Introduction ##
Assuming the project file has been generated, the workflow of using RSA key can be divided into these steps:
- Generate BOOT.BIN, which includes the authentication information of each partition needs to be authenticated
- Program RSA keys into ZYNQ

When generating BOOT.bin, two flows can be used: debug mode and release mode. 
Debug mode is used when you have the secure key. Release mode is used when only public key is available.
Debug mode is simple to operate. It automates the sign procedure with bootgen. But it's not that secure because the secure key should only be accessible by specific privilege. If the secure key is leaked, the secure environment is not secure any more. So this mode is commonly used in lab environment for testing.
Release mode separates the partition signing and image generation so that the signing procedure is more easier to be managed with privilege control.

Since RSA keys are in PS side, the RSA keys programming is controlled by PS CPU. 
A program for ARM core needs to be prepared. Some specific running condition needs to be considered for this specific program. 
The program launch environment for manufactory should also be considered. We will discuss the details.


## Debug Mode Image Generation ##

## Release Mode Image Generation ##

## Program RSA keys ##
