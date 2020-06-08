      subroutine rassech	!  Подпрограмма расчета сечений.
c--------------------------------------------------------------
      include   'inits.fn'
      real*4    le,lemax,e,sm,sm1,er,p,ht,te,ex1s,ex3s,ex1d,
     >          ex3d,ex1p,ex3p,pi,pm1,pm2
      integer*2 i
      parameter (pi=3.1415926536,pm1=2.8974,pm2=3.3)

c-----------elas and total-------------------------------------

      write(*,*)' ----------elastic and total---------'
      stot(0)=1./sela(0.)/pm2           !***********
      selas(0)=stot(0)
      sm1=0.
      ht=pi/float(nser-1)
      do te=0.,pi,ht
        sm1=sm1+seladi(0.,te)*ht
      enddo
      sm=0.
      te=0.
      do j=1,nu-1
        spelas(j,0)=pi*(1.-sm/sm1)
        do k=1,nser/(nu-1)
          sm=sm+seladi(0.,te)*ht
	  te=te+ht
        enddo
      enddo
      spelas(nu,0)=0.
      sm=sm
      lemax=log(emax)
      hestl=lemax/float(nser-1)
      i=1
      do le=0.,lemax+hestl/4.,hestl
	e=exp(le)
        selas(i)=1./sela(e)/pm2   !**********
	sm1=0.
        ht=pi/float(nser-1)
	do te=0.,pi,ht
	  sm1=sm1+seladi(e,te)*ht
	enddo
	sm=0.
	te=0.
	do j=1,nu-1
          spelas(j,i)=pi*(1.-sm/sm1)
          do k=1,nser/(nu-1)
	    sm=sm+seladi(e,te)*ht
	    te=te+ht
	  enddo
	enddo
        spelas(nu,i)=0.
	ex1s=0.
	ex3s=0.
	ex1d=0.
	ex3d=0.
	ex1p=0.
	ex3p=0.
        do l=2,10
	  ex1s=ex1s+se1s(e,l,p)
	  ex3s=ex3s+se3s(e,l,p)
	  if(l.ge.3)then
	    ex1d=ex1d+se1d(e,l,p)
	    ex3d=ex3d+se3d(e,l,p)
	  endif
	  ex1p=ex1p+se1p(e,l,p)
	  ex3p=ex3p+se3p(e,l,p)
	enddo
        stot(i)=1./(1./selas(i)+(ex1s+ex3s+ex1d+ex3d+
     >         ex1p+ex3p+sioniz(e,pion))*pm1)  !************
	i=i+1
      enddo

c-----------ionization----------------------------------------------

      write(*,*)' ----------ionization---------'
      lemax=log(emax/pion)
      hesil=lemax/float(nser-1)
      i=1
      do le=0.,lemax+hesil/4.,hesil
        e=pion*exp(le)
        sion(i)=sioniz(e,pion)*pm1   !*******
	if(le.eq.0.)goto 555
	sm1=0.
        ek=(e-pion)/2.
        he=ek/float(nser-1)
	do er=0.,ek,he
	  sm1=sm1+siondi(e,er)*he
	enddo
	sm=0.
	er=0.
	do j=1,nu-1
          spion(j,i)=sm/sm1
          do k=1,nser/(nu-1)
	    sm=sm+siondi(e,er)*he
	    er=er+he
	  enddo
	enddo
        spion(nu,i)=.99999
        spion(1,i)=.00001
  555   i=i+1
      enddo

c-----------exited------------------------------------------------

      write(*,*)' ----------exited---------'
      le=se3s(0.,2,pexi(1))
      do i=1,nexp
        lemax=log(emax/pexi(i))
        hesel(i)=lemax/float(nser-1)
	j=1
        do le=0.,lemax+hesel(i)/4.,hesel(i)
          e=pexi(i)*exp(le)
	  ex1s=0.
	  ex3s=0.
	  ex1d=0.
	  ex3d=0.
	  ex1p=0.
	  ex3p=0.
	  do l=2,10
	    ex1s=ex1s+se1s(e,l,p)
	    ex3s=ex3s+se3s(e,l,p)
	    if(l.ge.3)then
	      ex1d=ex1d+se1d(e,l,p)
	      ex3d=ex3d+se3d(e,l,p)
	    endif
	    ex1p=ex1p+se1p(e,l,p)
	    ex3p=ex3p+se3p(e,l,p)
          enddo
          sexi(i,j)=(ex1s+ex3s+ex1d+ex3d+ex1p+ex3p)*pm1 !*********
	  j=j+1
	enddo
      enddo
      return
      end
