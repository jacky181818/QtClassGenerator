# 类生成器 for Qt

	给定要生成的类的类名、基类名称以及成员变量列表，软件会根据信息生成对应的类申明和实现，主要用于网络通讯Json对象的串化和反串化，具体见下面使用说明。    
	
---

## 使用说明

### 1. 需要的信息


类名：myClass    
基类名：QObject    
成员变量列表（举例如下）：   
```
int age; //年龄
QString name; //姓名
QString address; //住址
QString mobile; /* 手机号码 */
```
	  
![类生成前信息](https://raw.githubusercontent.com/jacky181818/QtClassGenerator/master/image/Image1.PNG)

### 2. 生成类

点击【生成】按钮，会生成如下信息：

类声明：   
```
class myClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int age MEMBER age)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString address MEMBER address)
    Q_PROPERTY(QString mobile MEMBER mobile)

public:
    Q_INVOKABLE myClass(QObject *parent = nullptr);
    myClass(const myClass &obj);
    myClass & operator = (const myClass &obj);
    int age; 	//年龄
    QString name; 	//姓名
    QString address; 	//住址
    QString mobile; 	/* 手机号码 */

private:
    void copyValue(const myClass &obj);
}
```	

类实现：    
```
myClass::myClass(QObject *parent) : QObject(parent)
{

}

myClass::myClass(const myClass &obj)
{
    copyValue(obj);
}

myClass &myClass::operator = (const myClass &obj)
{
    copyValue(obj);
    return *this;
}

void myClass::copyValue(const myClass &obj)
{
    age                      = obj.age;
    name                     = obj.name;
    address                  = obj.address;
    mobile                   = obj.mobile;
}
```

![类生成后信息](https://raw.githubusercontent.com/jacky181818/QtClassGenerator/master/image/Image2.PNG)
	