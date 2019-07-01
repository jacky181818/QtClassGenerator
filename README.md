# �������� for Qt

	����Ҫ���ɵ�������������������Լ���Ա�����б�����������Ϣ���ɶ�Ӧ����������ʵ�֣���Ҫ��������ͨѶJson����Ĵ����ͷ����������������ʹ��˵����    
	
---

## ʹ��˵��

### 1. ��Ҫ����Ϣ


������myClass    
��������QObject    
��Ա�����б��������£���   
```
int age; //����
QString name; //����
QString address; //סַ
QString mobile; /* �ֻ����� */
```
	  
![������ǰ��Ϣ](https://raw.githubusercontent.com/jacky181818/QtClassGenerator/master/image/Image1.PNG)

### 2. ������

��������ɡ���ť��������������Ϣ��

��������   
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
    int age; 	//����
    QString name; 	//����
    QString address; 	//סַ
    QString mobile; 	/* �ֻ����� */

private:
    void copyValue(const myClass &obj);
}
```	

��ʵ�֣�    
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

![�����ɺ���Ϣ](https://raw.githubusercontent.com/jacky181818/QtClassGenerator/master/image/Image2.PNG)
	