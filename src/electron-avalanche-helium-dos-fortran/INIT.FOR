        include 'sear.fn'
        character*30 name
        logical trg
c--------------------------------------------------------------
        open(unit=1,file='d.ddd',status='unknown')
          read(1,*)ff
          read(1,*)dk
          read(1,*)d0
          read(1,*)ff1
          read(1,*)maxf0
          read(1,*)nele
          read(1,*)name
        close(1)
	hx0=d0/(nsx-1)
	ii=nsx/nsf
	fff=ff*2.d0/dk
	j=0
        do i=1,nsx
          x=(i-1)*hx0
          xs(i)=x
          if(dk.gt.0.)then
	    if(x.lt.dk)then
              field(i)=fff*(dk-x)
	    else
              field(i)=ff1
            endif
	  else
	    field(i)=ff
	  endif   
	  if(mod(i,ii).eq.0.and.j.lt.nsf)then
	    j=j+1
            numf(i)=j
	  else
	    numf(i)=0
	  endif
        enddo
        write(*,*)'nsx=',nsx,'  nsf=',nsf,'  nse=',nse
        write(*,*)'------ nsx ---- xs -------- field ---------- numf --'
        do i=1,nsx
          write(*,*)i,xs(i),field(i),numf(i)
        enddo
	write(*,*)'------ parameters : --------------------------------'
	write(*,*)'x_step=',hx0,'   x_length=',d0
	write(*,*)'dk=',dk
	write(*,*)'maxf0=',maxf0
	write(*,*)'nele=',nele
	write(*,*)' file--> ',name
	write(*,*)'------ Create base file. ---------------------------'
        inquire(file='rnd.tec',exist=trg)
        open(unit=1,file='rnd.tec',status='unknown',
     &       form='formatted')
        if(trg)then
          read(1,*)rand
        else
          rand=987654321.d0
          write(1,*)rand
        endif
        close(unit=1)
        open(unit=5,file=name,status='unknown',
     >     form='unformatted')
	include 'write.fn'
        close(unit=5)
	write(*,*)'------ File created successful ! -------------------'
	END


