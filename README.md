# SRPAAS_Sdk
通过JNI实现android与c++的完美通讯，实现会议的交互

#说明
通过Application中的PlatFormTypeBox设置，编译不同的so库

#调用流程
loadLibrary加载所需要的so
初始化会议，创建JNI线程；
sdk通过C++的callBack传递信令，java通过JNI的callVoidMethod接受信令，做出相应的处理；





