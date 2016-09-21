在正式烧写前，请确保该工程的makefile符合你手上的控制器型号

此程序是HANDSFREE的主控出厂测试程序： 

测试流程：
插上jlink
插上usb串口，打开串口助手连上（ubuntu下用cutecom串口助手）
插上电机驱动和电机
烧写测试control unit v2的程序：
OpenRE/0_Project/Application/Control_Unit_Test/linux

测试现象：
1. 4个io_led以20HZ频率在闪
2. 蜂鸣器以20HZ频率在叫
3. 四个电机的现象是 
    while（1）
    {
      顺时针转5秒，速度是1000度每秒
      逆时针转5秒，速度是1000度每秒
    }    
    这个现象可以同时用于测试主控的电机驱动接口，电机驱动，电机编码器是否正常

4. 插上串口 ，打开串口助手 可以看到一直在打印四个电机的速度： 正常情况速度应该是1000  或者 -1000   
    printf("measure motor speed:  motor1=%.4f  motor2=%.4f  motor3=%.4f  motor4=%.4f \r\n" , motor1.get_measure_angle_speed() , motor2.get_measure_angle_speed() , motor3.get_measure_angle_speed() , motor4.get_measure_angle_speed() );
    
5. 用串口助手发送任意字符，串口会接收到同样的字符（用于测试主控的串口接收和发送） 

以上的测试都成功后就可以烧写固件了，出厂预烧固件是   
OpenRE/0_Project/Application/Wheel_Robot_Beta/linux


