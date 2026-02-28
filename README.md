# Darkforest_test
A personal project of making a Darkforest Simulator, and also a practice of the GitHub Flow.

I'm sorry that I only made a Chinese version. Since I am a student and my English is poor, there will possibly NOT be an English version in the future.

***

这是我初中做的一个黑暗森林模拟器（已经过去4年了啊……），目前的是 **4.1版本**

感谢我的同学和网友们，给我之前的版本不断提出了建议

4.1版本包含：
* 黑暗森林打击（光粒，二向箔，奇点炸弹，制造光墓）
* 宇宙安全声明：黑域
* 交流&广播
* 星舰文明战争
* 文明名称

一些设定：
```
sci<=15 原始时代
15<sci<=25 科学时代
25<sci<=30 核能时代
30<sci<=35 电磁时代
35<sci<=45 星舰时代
45<sci<=50 引力波时代
50<sci<=60 微观时代
60<sci<=80 曲率时代
80<sci<=100 光粒/奇点炸弹时代
sci>100 归零时代 
```

目前版本非常不完善的，但我也不太可能再做进一步维护了

附带了数据制造器，默认文明名称为“X号文明”，如果有需要请手动改名

关于一些bug：

* 运行后好几分钟程序还没结束
> 建议直接终止运行。实际上正常比较小的数据（文明个数10以内）如果15秒还出不来就可以终止运行了，毕竟程序里包含大量随机数一不小心运气不好就会导致最后的几个文明打都打不起来……
* 搞了1000个文明结果炸了
> 在程序中设置的文明数量上限是100，你搞1000个当然不行了……而且我仍未试过100个文明的数据，不确定会花多久，发生什么情况……毕竟一般测试10个数据也差不多了……
