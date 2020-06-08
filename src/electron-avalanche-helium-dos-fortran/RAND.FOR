      Subroutine rnd(rn,i)
      Real*8 rn,rand(15)
       Common/rand/rand
      rand(i)=dmod(16807.d0*rand(i),2147483647.d0)
      rn=rand(i)*.4656612873077392258d-09
      Return
      End
