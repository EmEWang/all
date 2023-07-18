#include <bits/stdc++.h>

void drivecallbase();

int main()
{
    drivecallbase();

    return 0;
}


class base
{
    public:
    void a(){printf("base.a\n");}
    virtual void  b(){printf("base.b\n");}
};
class drive : public base
{
    public:
    void a(){printf("drive.a\n");}
    virtual void  b(){printf("drive.b\n");}
};
void drivecallbase()
{
    drive d;
    base* pb = new drive;
    drive* pd = new drive;

    d.a();      // drive.a
    d.b();      // drive.b
    d.base::a();      // base.a
    d.base::b();      // base.b
    pb->base::a();      // base.a
    pb->base::b();      // base.b
    pd->base::a();      // base.a
    pd->base::b();      // base.b
}