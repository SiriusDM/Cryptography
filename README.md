# 密码学原理课程设计

## Problem 1 SPN实现

1. **SPN过程**

   1.1 轮密钥异或 

   1.2 S盒代换

   1.3 P盒置换

2. **SPN流程图**

   ![image-20200912111544083](https://gitee.com/KinDog/picgo/raw/master/picture/image-20200912111544083.png)

   3. **代码流程**

      ![image-20200912111129562](https://gitee.com/KinDog/picgo/raw/master/picture/image-20200912111129562.png)

      ![image-20200912111653181](https://gitee.com/KinDog/picgo/raw/master/picture/image-20200912111653181.png)

   4. **优化**

      + 快速读入
      + S盒P盒打表

   ## Problem 2 SPN线性分析

   1. **算法流程**

      根据选定的线性逼近的链和给出的8000对明-密文对计算计数器，选取计数器最大的密钥对最为候选子密钥

      ![image-20200912125907253](https://gitee.com/KinDog/picgo/raw/master/picture/image-20200912125907253.png)

      ![image-20200912125931230](https://gitee.com/KinDog/picgo/raw/master/picture/image-20200912125931230.png)

   2. **分析**

      + 首先给出了一条关于K2，K4的链，直接使用而暴力剩余24位密钥超过要求时间的复杂度，考虑寻找第二条链用于减少枚举位数

      + 选取了一条链后，新选取的链涉及到4个密钥，需要以Count值高的候选子密钥设为已知来求K1,K3，由于选取的链性能不好，正确候选子密钥的Count值未必最高或同Count值的候选子密钥过多导致TLE

      + 考虑选取第三条链来修正K1,K3的值，处理同第二条链，取两条线性逼近的链的Count的绝对值之为作为K1,K3的key值排序，这样可以通过前7个测试点，最后三个点还是TLE。

      + 经过调整参数测试，发现给定的第一条链性能不够优秀，直接选取第4条链对K2,K4进行修正，处理同第一条链。

      + 最终再枚举剩余16位密钥

      + **K2,K4**  (x5,x7,x8)(u6,u8,u14,u16)

        ​			  (x13,x15)(u7,u15)

        **备选链**   (x9,x11)(u7,u15)

        **K1,K3**  (x1,x2,x4)(u1,u5,u9,u13)

        ​		     (x9,x10,x12)(u3,u7,u11,u15)

   3. **优化**

      + 快速读入
      + S盒P盒打表
      + 求出正确密钥后结束循环

   

   

   

   