#ifndef __NOCOPY_CLASS_HPP__
#define __NOCOPY_CLASS_HPP__
class NocopyClass
{
    public:
    NocopyClass()=default;
    private:

    NocopyClass(const NocopyClass&)=delete;
    NocopyClass& operator = (const NocopyClass&)=delete;
};
#endif