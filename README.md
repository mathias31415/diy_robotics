# diy_robotics

## Overview

This repo contains the results of a project work at the University of Applied Sciences Karlsruhe by **Robin Wolf, Hannes Bornemann and Mathias Fuhrer**. As part of the project work, the [Six-Axis Robot Arm WE-R2.4 from LoboCNC](https://www.printables.com/de/model/132260-we-r24-six-axis-robot-arm) was set up and a new gripper was developed.

![Robot_blur](images/Robot_blur.png)

The CAD files of the gripper and assembly instructions can be found in folder [diy_robotics_gripper_cad](https://github.com/mathias31415/diy_robotics/tree/main/diy_robotics_gripper_cad).

![img7](diy_robotics_gripper_cad/images/img7.png)

Two PCBs were designed for the electrical wiring: one PCB for the 6 axes and one PCB for the gripper. The KiCAD and Gerber files can be found in the folders [diy_robotics_arm_pcb](https://github.com/mathias31415/diy_robotics/tree/main/diy_robotics_arm_pcb) and [diy_robotics_gripper_pcb](https://github.com/mathias31415/diy_robotics/tree/main/diy_robotics_gripper_pcb).
![pcb_arm_and_gripper](images/pcb_arm_and_gripper.png)

To control the 6 axes and the gripper, ROS2 implementations were written that communicate via Wifi with an ESP32, from which the axes and the gripper are then moved. One ESP32 is responsible for the 6 axes, and the second ESP32 is responsible for the gripper.

The ROS2 packages are packaged in Docker containers so that they can be used by others without any problems. The repos of our ROS2 packages are linked in the folder [ROS-Packages](https://github.com/mathias31415/diy_robotics/tree/main/ROS-Packages). To just use our ROS application go to the repo [diy_robot_application](https://github.com/RobinWolf/diy_robot_application) and follow the HowTo. To understand our implementation you should read all readmes of our ROS repos 

The PC on which the ROS2 packages are executed must be connected to the same Wifi as the two ESP32s. The two ESP32s then receive messages from the PC via TCP-IP with the commands for the gripper and the 6-axes and then control the gripper and the axes accordingly. The VS-Code PlatformIO project folders for the ESP32 of the gripper and the axes can be found in the folders [diy_robotics_arm_esp32](https://github.com/mathias31415/diy_robotics/tree/main/diy_robotics_arm_esp32) and [diy_robotics_gripper_esp32](https://github.com/mathias31415/diy_robotics/tree/main/diy_robotics_gripper_esp32). Make sure to adapt the SSID and IP address as well as the password of your Wifi in the ``Configuration.h`` file.


The [hardwaretest_without_ROS](https://github.com/mathias31415/diy_robotics/tree/main/hardwaretest_without_ROS) folder contains additional programs to test the hardware without ROS via the Serial Monitor.


## Possible improvements

- Conversion of the robot to metric screws
- Endstops or sensors to determine the position of the robot or to move it to a home position


## Part list (as of March 2024)
The information serves as a guide only. Prices may change over time. It is also worth comparing other providers and manufacturers.
(Parts such as screws, filament and glue are not listed)

### 1. Robot-arm
| Index | Description | Quantity | Total price in € | Link |
| --- | --- | --- | --- | --- |
| 1 | Nema 17 Stepper-Motor 42Ncm | 3 | 15,55 | [Link](https://www.omc-stepperonline.com/de/3-stueck-e-serie-nema-17-bipolar-42-ncm-59-49-oz-in-1-5a-42x42x38mm-4-draehte-3-17he15-1504s) |
| 2 | Minibea PM35L-048 Stepper-Motor | 3 | 18,20 | [Link](https://www.ebay.de/itm/403845575203?_trkparms=amclksrc%3DITM%26aid%3D777008%26algo%3DPERSONAL.TOPIC%26ao%3D1%26asc%3D20230811123857%26meid%3D01b980ffd3f64d67a8210c3d282fd210%26pid%3D101770%26rk%3D1%26rkt%3D1%26itm%3D403845575203%26pmt%3D1%26noa%3D1%26pg%3D4375194%26algv%3DRecentlyViewedItemsV2%26brand%3DMarkenlos&_trksid=p4375194.c101770.m146925&_trkparms=parentrq%3Acd81805118b0a8cc93d6ff8cffffc172%7Cpageci%3Aa6388820-82dd-11ee-97f3-8e07020e1f61%7Ciid%3A1%7Cvlpname%3Avlp_homepage) |
| 3 | 6mm steel balls for bearings | 200 | 9,99 | [Link](https://www.amazon.de/dp/B01LPZ56ZC?psc=1&ref=ppx_yo2ov_dt_b_product_details ) |
| 4 | additional connection cable for motors 1,5m | 6 | 9,59 | [Link](https://www.amazon.de/Iverntech-Schrittmotor-Terminal-3D-Drucker-Stepper/dp/B08SQ35LRQ/ref=sr_1_6?crid=2UUMN13RQ0TTT&keywords=stepper%2Bmotor%2Bkabel&qid=1700576677&sprefix=stepper%2Bmotor%2B%2Caps%2C149&sr=8-6&th=1 ) |
| 5 | Power supply 24V 350W | 1 | 22,97 | [Link](https://www.omc-stepperonline.com/de/lrs-350-24-mean-well-350w-24vdc-14-6a-115-230vac-geschlossenes-schaltnetzteil-lrs-350-24) |
| 6 | Step-Down Converter 24V - 5V | 2 | 4,00 | [Link](https://www.amazon.de/Yizhet-Converter-Spannungsregler-Einstellbares-Abw%C3%A4Rtsmodul/dp/B0CKWYXD89/ref=sr_1_2_sspa?keywords=step+down+modul&qid=1699960183&sr=8-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1) |



### 2. Gripper
| Index | Description | Quantity | Total price in € | Link |
| --- | --- | --- | --- | --- |
| 1 | Servo MG90s Continous Drive | 2 | 9,00 | [Link](https://de.aliexpress.com/item/1005004550512467.html?spm=a2g0o.order_list.order_list_main.10.12875c5fjUap8p&gatewayAdapt=glo2deu) |

### 2. PCBs
The geber-files for the PCBs can be found in folders [diy_robotics_arm_pcb](https://github.com/mathias31415/diy_robotics/tree/main/diy_robotics_arm_pcb) and [diy_robotics_gripper_pcb](https://github.com/mathias31415/diy_robotics/tree/main/diy_robotics_gripper_pcb). With the geber-files, the PCBs can be ordered from any manufacturer. At JLCPCB we paid a total of just over €30 for 5 pieces of both PCBs.
The parts for assembling the PCBs are listed below. Note that some parts are required for both PCBs and are therefore listed twice. However, one set is often sufficient for both PCBs (e.g. for the pin headers). For components such as the ESP-32, it is cheaper to buy a set of two for both PCBs than to order two individual ESP-32s.

#### 2.1 Arm PCB
| Index | Description | Quantity | Total price in € | Link |
| --- | --- | --- | --- | --- |
| 1 | 0.96 Inch OLED Display SSD1306 | 1 | 1,78 | [Link](https://de.aliexpress.com/item/1005005970901119.html?spm=a2g0o.order_list.order_list_main.22.4a065c5ffRtZfv&gatewayAdapt=glo2deu) |
| 2 | ESP-32 | 1 | 10,00 | [Link](https://www.amazon.de/gp/aw/d/B074RG86SR/?_encoding=UTF8&pd_rd_plhdr=t&aaxitk=6a9e09b157f2b15a9cc364c1aba715aa&hsa_cr_id=4742246160502&qid=1699959775&sr=1-1-e0fa1fdd-d857-4087-adda-5bd576b25987&ref_=sbx_be_s_sparkle_mcd_asin_0_title&pd_rd_w=ee0VR&content-id=amzn1.sym.6f8b36f0-c2c9-44f2-97a8-5b151d2fc9c7%3Aamzn1.sym.6f8b36f0-c2c9-44f2-97a8-5b151d2fc9c7&pf_rd_p=6f8b36f0-c2c9-44f2-97a8-5b151d2fc9c7&pf_rd_r=0TBV9VYJCQK5QB253DBZ&pd_rd_wg=KZCjO&pd_rd_r=297525bc-30e7-47c9-996a-8a255adffee4)  |
| 3 | 2-Pin Screw Terminal 5mm | 3 | 4,56 for a set | [Link](https://de.aliexpress.com/item/1005005595075178.html?spm=a2g0o.order_list.order_list_main.17.4a065c5ffRtZfv&gatewayAdapt=glo2deu) |
| 4 | Pin Header 1x4 Pin Male 2,54mm | 6 |1,77 for male + female set | [Link](https://de.aliexpress.com/item/4000873858801.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.2.e4a5600cBKuomq&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=c41c94ec-099f-42bf-a647-59697bc6a5d5&_t=gps-id:pcDetailTopMoreOtherSeller,scm-url:1007.40050.354490.0,pvid:c41c94ec-099f-42bf-a647-59697bc6a5d5,tpp_buckets:668%232846%238114%231999&pdp_npi=4%40dis%21EUR%211.77%211.77%21%21%211.89%211.89%21%4021038dfc17098923902746506e96e7%2110000010058190554%21rec%21DE%213958237401%21&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A) |
| 5 | Capacitor 25V 100uF | 6 | 1,78 for 50pcs | [Link](https://de.aliexpress.com/item/1005005945738204.html?spm=a2g0o.order_list.order_list_main.11.4a065c5ffRtZfv&gatewayAdapt=glo2deu) |
| 6 | DRV8825 Stepper Driver | 6 | 10,00 |  [Link](https://www.amazon.de/dp/B07YFS29W7?psc=1&ref=ppx_yo2ov_dt_b_product_details ) |
| 7 | 4-way DIP-Switch 2,54mm | 6 | 1,86 for 10pcs | [Link](https://de.aliexpress.com/item/1005006109195564.html?spm=a2g0o.order_list.order_list_main.10.4a065c5ffRtZfv&gatewayAdapt=glo2deu) |
| 8 | Female pin header 2,54mm for the display, ESP-32 and Stepper Drivers |  | 1,77 for male + female set | [Link](https://de.aliexpress.com/item/4000873858801.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.2.e4a5600cBKuomq&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=c41c94ec-099f-42bf-a647-59697bc6a5d5&_t=gps-id:pcDetailTopMoreOtherSeller,scm-url:1007.40050.354490.0,pvid:c41c94ec-099f-42bf-a647-59697bc6a5d5,tpp_buckets:668%232846%238114%231999&pdp_npi=4%40dis%21EUR%211.77%211.77%21%21%211.89%211.89%21%4021038dfc17098923902746506e96e7%2110000010058190554%21rec%21DE%213958237401%21&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A) |


#### 2.2 Gripper PCB
| Index | Description | Quantity | Total price in € | Link |
| --- | --- | --- | --- | --- |
| 1 | 0.96 Inch OLED Display SSD1306 | 1 | 1,78 | [Link](https://de.aliexpress.com/item/1005005970901119.html?spm=a2g0o.order_list.order_list_main.22.4a065c5ffRtZfv&gatewayAdapt=glo2deu) |
| 2 | ESP-32 | 1 | 10,00 | [Link](https://www.amazon.de/gp/aw/d/B074RG86SR/?_encoding=UTF8&pd_rd_plhdr=t&aaxitk=6a9e09b157f2b15a9cc364c1aba715aa&hsa_cr_id=4742246160502&qid=1699959775&sr=1-1-e0fa1fdd-d857-4087-adda-5bd576b25987&ref_=sbx_be_s_sparkle_mcd_asin_0_title&pd_rd_w=ee0VR&content-id=amzn1.sym.6f8b36f0-c2c9-44f2-97a8-5b151d2fc9c7%3Aamzn1.sym.6f8b36f0-c2c9-44f2-97a8-5b151d2fc9c7&pf_rd_p=6f8b36f0-c2c9-44f2-97a8-5b151d2fc9c7&pf_rd_r=0TBV9VYJCQK5QB253DBZ&pd_rd_wg=KZCjO&pd_rd_r=297525bc-30e7-47c9-996a-8a255adffee4) |
| 3 | 2-Pin Screw Terminal 5mm | 2 | 4,56 for a set | [Link](https://de.aliexpress.com/item/1005005595075178.html?spm=a2g0o.order_list.order_list_main.17.4a065c5ffRtZfv&gatewayAdapt=glo2deu) |
| 4 | Pin Header 1x4 Pin Male 2,54mm | 1 | 1,77 for male + female set | [Link](https://de.aliexpress.com/item/4000873858801.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.2.e4a5600cBKuomq&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=c41c94ec-099f-42bf-a647-59697bc6a5d5&_t=gps-id:pcDetailTopMoreOtherSeller,scm-url:1007.40050.354490.0,pvid:c41c94ec-099f-42bf-a647-59697bc6a5d5,tpp_buckets:668%232846%238114%231999&pdp_npi=4%40dis%21EUR%211.77%211.77%21%21%211.89%211.89%21%4021038dfc17098923902746506e96e7%2110000010058190554%21rec%21DE%213958237401%21&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A) |
| 5 | Female pin header 2,54mm for the display, ESP-32 and Stepper Drivers |  |1,77 for male + female set | [Link](https://de.aliexpress.com/item/4000873858801.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.2.e4a5600cBKuomq&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=c41c94ec-099f-42bf-a647-59697bc6a5d5&_t=gps-id:pcDetailTopMoreOtherSeller,scm-url:1007.40050.354490.0,pvid:c41c94ec-099f-42bf-a647-59697bc6a5d5,tpp_buckets:668%232846%238114%231999&pdp_npi=4%40dis%21EUR%211.77%211.77%21%21%211.89%211.89%21%4021038dfc17098923902746506e96e7%2110000010058190554%21rec%21DE%213958237401%21&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A) |
