#include <iostream>
#include <string>

using namespace std;

class IFilled{
    public:
        virtual void description() = 0;
};

class FilledCircle : public IFilled{
    public:
        void description(){
            cout<<"Filled Circle.\n";
        }
};

class FilledSquare : public IFilled{
    public:
        void description(){
            cout<<"Filled Square.\n";
        }
};

class IOutlined{
    public:
        virtual void description() = 0;
};

class OutlinedCircle : public IOutlined{
    public:
        void description(){
            cout<<"Outlined Circle.\n";
        }
};

class OutlinedSquare : public IOutlined{
    public:
        void description(){
            cout<<"Outlined Square.\n";
        }
};

class IFactory{
    public:
        virtual IFilled* createFilledShape() = 0;
        virtual IOutlined* createOutlinedShape() = 0;
};

class CircleFactory : public IFactory{
    public:
        IFilled* createFilledShape(){
            return new FilledCircle();
        }
        IOutlined* createOutlinedShape(){
            return new OutlinedCircle();
        }
};

class SquareFactory : public IFactory{
    public:
        IFilled* createFilledShape(){
            return new FilledSquare();
        }
        IOutlined* createOutlinedShape(){
            return new OutlinedSquare();
        }
};

class ShapeAbstractFactory{
    public:
        static IFactory* CreateFactory(string shapeType){
            if(shapeType=="Circle")
                {return new CircleFactory();}
            {return new SquareFactory();}
        }
};

int main(){
    string shapeType;
    cout<<"Enter shape type :\n";
    cin>> shapeType;

    IFactory* fact = ShapeAbstractFactory::CreateFactory(shapeType);

    IFilled* filled = fact->createFilledShape();
    filled->description();

    IOutlined* outlined = fact->createOutlinedShape();
    outlined->description();

    return 0;
}