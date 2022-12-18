#include <cmath>
#include <iostream>

int main() {
    long double x;
    long double two = 2;
    long double e = exp(1);
    long double res;
    std::cout << "Input x\n";
    std::cin >> x;

    __asm {

        ;e^ x
        fld qword ptr[x]
        fld qword ptr[e]
        fyl2x
        fld st
        frndint
        fsub st(1), st
        fxch st(1)
        f2xm1
        fld1
        faddp st(1), st
        fscale
        fstp st(1)
        fst qword ptr[res]

        ;1 / e ^ x
        fld1
        fdiv qword ptr[res]

        ;e^ x + 1 / (e ^ x)
        fadd st, st(1)

        ;cosh(x)
        fdiv qword ptr[two]

        ;
        fstp qword ptr[res]
    }
    std::cout << "cosh(x) " << res << '\n';
    std::cout << "error rate " << abs(res - cosh(x)) << '\n';
    return 0;
}