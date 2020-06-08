      SUBROUTINE lav()
c--------------------------------------------------------------
      include   'sear.fn'
c--------------------------------------------------------------
      parameter (ionsmax=777)
      integer*2 is(ionsmax)
      real*8    xhr(ionsmax),ehr(ionsmax),chr(ionsmax)
      real*8    mi,mis,mn,ms,let,pi2
      parameter (pi2=2.d0*3.141592653589793238462643d0)
      parameter (pi=3.141592653589793238462643d0)
      logical   direct,dirs,dirstar
c--------------------------------------------------------------
      ilav=0
      ions=0
      call nach(et,cosf,maxf0)
      epop=et*(1.d0-cosf*cosf)
      iset=1
      hx0=xs(iset+1)-xs(iset)
      hx=hx0   
      direct=.true.
      dirstar=.true.
      xt=0.d0
      fieldt=field(1)
      vn=dsqrt(et)
      if(et.gt.1.d0)then
        let=log(et)
        ieto=idint(let/hestl)+1
        peto=(let-hestl*float(ieto-1))/hestl
      else
	ieto=0
	peto=et
      endif
      qt=1./((1.d0-peto)*stot(ieto)+peto*stot(ieto+1))
      vvv=1.d0/vn/cosf
      INCLUDE 'count.fn'
      iset=2
 33   sinf=1.d0-cosf*cosf
      epop=et*sinf
      sinf=dsqrt(sinf)
      vxn=dsqrt(et-epop)
      if(et.gt.1.d0)then
        let=log(et)
        ieto=idint(let/hestl)+1
        peto=(let-hestl*float(ieto-1))/hestl
      else
	ieto=0
	peto=et
      endif
      qt=1./((1.d0-peto)*stot(ieto)+peto*stot(ieto+1))
      mn=qt*dsqrt(et)/fieldt
 9    qi=0.d0
      call rnd(rn,1)
      rn=-dlog(1.d0-rn)
 2    est=et
      xst=xt
      vxst=vxn
      fields=fieldt
      fieldt=field(iset)
      ms=mn
      rn=rn-qi
      xt=xst+hx
      et=est+(fieldt+fields)/2.d0*hx
      if(direct)goto 5
      if(et.le.epop)then
        e1=epop
        if(fieldt.eq.fields)then
          xt=xst+(e1-est)/fieldt
      else
        a=(fieldt-fields)/(xt-xst)
        xt=xst-(fields-dsqrt(fields*fields+2.d0*a*(e1-est)))/a
        endif
        et=e1
	ppot=(xt-xs(iset))/hx0
        fieldt=(1.d0-ppot)*field(iset)+ppot*field(iset+1)
        itip=10
      endif
      if(xt.le.0.d0)then
        iset=1
	goto 666
      endif
 5    vn=dsqrt(et)
      if(et.gt.1.d0)then
        let=log(et)
        ieto=idint(let/hestl)+1
        peto=(let-hestl*float(ieto-1))/hestl
      else
	ieto=0
	peto=et
      endif
      qt=1./((1.d0-peto)*stot(ieto)+peto*stot(ieto+1))
      mn=qt*vn/fieldt
      mi=dmax1(mn,ms)
      vxn=dsqrt(et-epop)
      sqns=dabs(vxn-vxst)
      qi=mi*2.d0*sqns
      if(qi.lt.rn)then
        mis=dmin1(mn,ms)
        qi=qi-(mi-mis)*sqns
        goto 3
      endif
      if(direct)then
        s1=vxst+rn/2.d0/mi
      else
        s1=vxst-rn/2.d0/mi
      endif
      e1=s1*s1+epop
      if(fieldt.eq.fields)then
        xt=xst+(e1-est)/fieldt
      else
        a=(fieldt-fields)/(xt-xst)
        xt=xst-(fields-dsqrt(fields*fields+2.d0*a*(e1-est)))/a
      endif
      et=e1
      ii=iset
      if(direct)ii=ii-1
      ppot=(xt-xs(ii))/hx0
      fieldt=(1.d0-ppot)*field(ii)+ppot*field(ii+1)
      if(et.gt.1.d0)then
        let=log(et)
        ieto=idint(let/hestl)+1
        peto=(let-hestl*float(ieto-1))/hestl
      else
	ieto=0
	peto=et
      endif
      qt=1./((1.d0-peto)*stot(ieto)+peto*stot(ieto+1))
      sinf=epop/et
      cosf=dsqrt(1.d0-sinf)
      sinf=dsqrt(sinf)
      if(.not.direct)cosf=-cosf
      qtt=mi*fieldt/dsqrt(et)
c--------------------------------------------------------------
      itip=1
      call rnd(rnst,2)
      pis=0.d0
      if(et.gt.pion) goto 111
      if(et.gt.pexi) goto 112
      goto 114
 111  let=log(et/pion)
      ieio=idint(let/hesil)+1
      peio=(let-hesil*float(ieio-1))/hesil
      q=(1.d0-peio)*sion(ieio)+peio*sion(ieio+1)
      pis=q/qtt
      if(pis.ge.rnst)then
        itip=4
        ilav=ilav+1
        call rnd(rnst,3)
        ii=idint(50.d0*rnst)+1
	et=et-pion
        eee=et*spion(ii,ieio)
        call rnd(rr,12)
        if(rr.le..5d0)then
          e1=eee
          e2=et-e1
        else
          e2=eee
          e1=et-e2
        endif
        ehr(ilav)=e2
        xhr(ilav)=xt
        is(ilav)=iset
        if(direct)is(ilav)=is(ilav)-1
        cosh1=dsqrt(e1/et)
        cosh2=dsqrt(e2/et)
        et=e1
        call rnd(r1,7)
        call rnd(r2,7)
        e1=cosf
        cosf=e1*cosh1+sinf*dsqrt(1.d0-cosh1*cosh1)*dcos(pi2*r1)
        chr(ilav)=e1*cosh2+sinf*dsqrt(1.d0-cosh2*cosh2)*dcos(pi2*r2)
	ions=ions+1
        goto 44
      endif
 112  let=log(et/pexi)
      ieex=idint(let/hesel)+1
      peex=(let-hesel*float(ieex-1))/hesel
      q=(1.d0-peex)*sexi(ieex)+peex*sexi(ieex+1)
      pis=pis+q/qtt
      if(pis.ge.rnst)then
        itip=3
        et=et-pexi
        goto 44
      endif
 114  q=1./((1.d0-peto)*selas(ieto)+peto*selas(ieto+1))
      pis=pis+q/qtt
      if(pis.ge.rnst)then
        itip=2
        call rnd(r1,6)
        ii=idint(50.d0*r1)+1
        hi=spelas(ii,ieto)
        coshi=dcos(hi)
        deltae=et*.2723083d-3*(1.d0-coshi)
        deel=deel+deltae
        et=et-deltae
        if(et.le.0.d0)then
          cosf=1.d0
          et=0.d0
        else
          call rnd(r2,7)
          cosf=cosf*coshi+sinf*dsin(hi)*dcos(pi2*r2)
        endif
      endif
 44   dirs=direct
      direct=cosf.ge.0.d0
      if(dirs.neqv.direct)then
        if(dirs)then
          iset=iset-1
        else
          iset=iset+1
        endif
      endif
      hx=dble(xs(iset))-xt
      epop=et*(1.d0-cosf*cosf)
      if(et.gt.1.d0)then
        let=log(et)
        ieto=idint(let/hestl)+1
        peto=(let-hestl*float(ieto-1))/hestl
      else
	ieto=0
	peto=et
      endif
      qt=1./((1.d0-peto)*stot(ieto)+peto*stot(ieto+1))
      mn=qt*dsqrt(et)/fieldt
      vxn=dsqrt(et-epop)
      goto 9
 3    if(itip.eq.10)then
        direct=.true.
        iset=iset+1
        itip=0
        hx=dble(xs(iset))-xt
        hx0=xs(iset)-xs(iset-1)
        goto 2
      endif
 666  sinf=epop/et
      cosf=dsqrt(1.d0-sinf)
      sinf=dsqrt(sinf)
      vn=dsqrt(et)
      INCLUDE 'count.fn'
      if(direct)then
        if(iset.eq.nsx)goto 8
        iset=iset+1
        hx0=xs(iset)-xs(iset-1)
      else
        if(iset.eq.1)goto 8
        iset=iset-1
        hx0=xs(iset+1)-xs(iset)
      endif
      hx=dble(xs(iset))-xt
      goto 2
 8    if(ilav.eq.0)goto 77
      xt=xhr(ilav)
      et=ehr(ilav)
      cosf=chr(ilav)
      dezap=et
      iset=is(ilav)
      ilav=ilav-1
      direct=cosf.ge.0.d0
      hx0=xs(iset+1)-xs(iset)
      ppot=(xt-xs(iset))/hx0
      fieldt=(1.d0-ppot)*field(iset)+ppot*field(iset+1)   
      if(direct)iset=iset+1
      hx=dble(xs(iset))-xt
      goto 33
 77   continue
      return
      end


