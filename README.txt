1、form是一个控件的ui文件 形状由qss设置 另外还有功能在form上设置
2、label的标志要做成三角形的 准备用图片贴上去
3、当form显示在widget上的时候，form的背景被widget的背景覆盖 form的背景似乎为透明的 问题未解决
4、这是一次做控件的尝试,相比于重绘和做成自定义控件,要简单，也让我看到的qss的方便易用

1、当一个控件的背景属性为透明,那么该控件会被父类的背景色所覆盖 此时可以设置父类
this->setAttribute(Qt::WA_TranslucentBackground);//半透明背景 ，此时控件就不会被遮盖
2、重绘图案中 复杂不规则图形的填充 可以由 QPainterPath与QPainter实现

2.控件大小固定不可伸缩