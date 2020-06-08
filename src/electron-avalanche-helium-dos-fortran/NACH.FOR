 	subroutine nach(en,cosf,er)
        implicit real*8 (a-h,o-z)
        real*8 rand(15),pi
        common/rand/rand
        parameter (pi=3.141592653589793238462643d0)
        call rnd(cosf,9)
        if(cosf.eq.0.d0)cosf=1.d-4
        call rnd(rn,8)
        rn=1.d0-rn*2.d0
        en=er*(dabs(dasin(rn)+pi/2.d0)/pi)**.9
        return
        end
