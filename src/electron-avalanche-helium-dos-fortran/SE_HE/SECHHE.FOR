с
с		Функции расчета сечений.
с
       real*4 function se1s(e,n,p)
       real*4 un(3),b0,en,e,p,unn
       data b0/.36/,un/0.,1.5152,1.6846/
       en=e/13.6058
       k=n
       if(n.gt.3)k=3
       unn=un(k) !#################
       p=unn*13.6058
       if(en.gt.unn)then
         se1s=4.*b0/float(n*n*n)/unn
     &         *sqrt(1.-unn/en)/en
       else
         se1s=0.
       endif
       return
       end

       real*4 function se3s(e,n,p)
       real*4 un(3),b0,en,e,p,unn
       data b0/2.24/,un/0.,1.4567,1.6697/
       en=e/13.6058
       k=n
       if(n.gt.3)k=3
       unn=un(k)  !#################
       p=unn*13.6058
       if(en.gt.unn.and.n.ge.2)then
         se3s=4.*b0/float(n*n*n)/unn
     &         *sqrt(1.-unn/en)/en**3
       else
        se3s=0.
       endif
       return
       end

       real*4 function se1d(e,n,p)
       real*4 un(3),b0,en,e,p,unn
       data b0/.33/,un/0.,0.,1.6959/
       en=e/13.6058
       k=n
       if(n.gt.3)k=3
       unn=un(k)  !#################
       p=unn*13.6058
       if(en.gt.unn.and.n.ge.3)then
         se1d=4.*b0/float(n*n*n)/unn
     &         *sqrt(1.-unn/en)/(en+unn)
       else
         se1d=0.
       endif
       return
       end

       real*4 function se3d(e,n,p)
       real*4 un(3),b0,en,e,p,unn
       data b0/1.24/,un/0.,0.,1.6958/
       en=e/13.6058
       k=n
       if(n.gt.3)k=3
       unn=un(k)  !#################
       p=unn*13.6058
       if(en.gt.unn.and.n.ge.3)then
         se3d=4.*b0/float(n*n*n)/unn
     &         *sqrt(1.-unn/en)/(en+unn)/en**2
       else
         se3d=0.
       endif
       return
       end

       real*4 function se1p(e,n,p)
       real*4 un(3),f(6),d,cn,en,e,g,p,a,
     >        as,bs,ds
       data f/0.,.2762,.0734,.0307,.0157,.0091/,
     >     un/0.,1.5595,1.6968/
       data as/.96/,bs/13./,ds/.05/,d/2./,cn/.65/
       en=e/13.6058
       k=n
       if(n.gt.3)k=3
       unn=un(k)  !#################
       p=unn*13.6058
       if(en.gt.unn.and.n.ge.2)then
         if(n.gt.6)then
           a=1.96/float(n*n*n)
         else
           a=f(n)
         endif
	 g=1.+as/en*(1.+bs/en)/(1.+(ds*en)**4)
         se1p=4.*(1.-(unn/en)**2)/en/unn/g
     &         *a*alog(d+cn*(en-unn))
       else
         se1p=0.
       endif
       return
       end

       real*4 function se3p(e,n,p)
       real*4 un(3),b0,en,e,p,unn
       data b0/10.8/,un/0.,1.5408,1.6909/
       en=e/13.6058
       k=n
       if(n.gt.3)k=3
       unn=un(k)  !#################
       p=unn*13.6058
       if(en.gt.unn.and.n.ge.2)then
         se3p=4.*b0/float(n*n*n)/unn
     &         *sqrt(1.-unn/en)/(en+unn)**3
       else
         se3p=0.
       endif
       return
       end

       real*4 function siondi(ene,ere)
       real*4 ene,ere,pi,pmi2,d,c1,w,a,b,f,s1,s2,s3
       data pmi2/.49/,d/1.6/,c1/.15/,w/67.7/,
     &      a/5.34/,b/.027/
       pi=1.808  !#################
       en=ene/13.6058
       er=ere/13.6058+pi
       f=a/en
       f=1.+f*(1.+f)/(1.+(b*en)**3)
       s1=1./(er**2)+1./((en+pi-er)**2)
     &    -(en+pi)/(en+w)/er/(en+pi-er)
       s2=1./(er**3)+1./((en+pi-er)**3)
       s3=alog(d+sqrt(c1*(en-pi)))
       siondi=(s1+2.*s2*pmi2*(pi**2)*s3)*8./en/f
       return
       end

       real*4 function sioniz(e,pio)
       real*4 e,en,pi,pmi2,d,c1,w,a,b,f,s1,s3,pio
       data pmi2/.49/,d/1.6/,c1/.15/,w/67.7/,
     &      a/5.34/,b/.027/
       pi=1.808  !#################
       en=e/13.6058
       pio=pi*13.6058
       if(en.gt.pi)then
         f=a/en
         f=1.+f*(1.+f)/(1.+(b*en)**3)
         s1=1./pi*(1.-pi/en)-1./(en+w)*alog(en/pi)
         s3=(1.-(pi/en)**2)*pmi2*alog(d+sqrt(c1*(en-pi)))
         sioniz=(s1+s3)*8./en/f
       else
	 sioniz=0.
       endif
       return
       end

       real*4 function sela(en)
       real*4 e(26),s(26),ee,eee,ss,sss,aa,bb
       data e/0,2,4,5,6,8,10,12,14,16,18,20,
     &          25,30,40,50,60,70,80,90,100,
     &         125,150,200,250,300/
     &      s/5.420,5.550,5.516,5.346,5.122,
     &        4.735,4.389,4.065,3.777,3.520,
     &        3.274,3.095,2.680,2.391,2.001,
     &        1.715,1.541,1.394,1.269,1.184,
     &        1.120,0.983,0.884,0.734,0.631,0.556/
       ee=e(25)
       eee=e(26)
       ss=1./s(25)
       sss=1./s(26)
       aa=(ss-sss)/(ee-eee)
       bb=sss-aa*eee
       if(en.ge.eee)then
         sela=1./(aa*en+bb)
       else
         call interpol(e,s,26,en,sela)
       endif
      return
      end

      real*4 function seladi(e,tet)
      real*4 e,tet
	seladi=exp(-.45*sqrt(e)*sin(tet/2.))
      return
      end

      subroutine interpol(x,y,n,xt,yt)
      real*4 x(*),y(*),xt,yt,yt1,yt2
      integer*2 i/1/
      i=1
      do while(x(i).lt.xt)
        i=i+1
      enddo
      if(i.ne.1)i=i-1
      yt=x(i)-x(i+1)
      if(i.ge.n-2)then
	yt=((xt-x(i+1))*y(i)-(xt-x(i))*y(i+1))/yt
      else
	yt1=x(i)-x(i+2)
	yt2=x(i+1)-x(i+2)
	yt=(xt-x(i+1))*(xt-x(i+2))/yt/yt1*y(i)-
     &     (xt-x(i))*(xt-x(i+2))/yt/yt2*y(i+1)+
     &     (xt-x(i))*(xt-x(i+1))/yt1/yt2*y(i+2)
      endif
      return
      end
