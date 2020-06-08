        interface to integer[C] function getch[C] ()
        end
        interface to integer[C] function kbhit[C]()
        end
c--------------------------------------------------------------
	include 'sear.fn'
	include 'time.fn'
	integer[c] kbhit,getch
	integer*4 ihh
	real*4 sec
	real*8 tn,tk,tt1  
        logical exited/.true./
c--------------------------------------------------------------
        include 'read_se.fn'
	open(15,file='rnd.tec')
	  read(15,*)rand
	close(15)
        open(unit=5,file=' ',status='old',form='unformatted')
	INCLUDE 'read.fn'
	write(*,*)' Welcome to main programm ! '
        write(*,*)'   pion=',pion,' pexi=',pexi
        write(*,*)'   kele=',kele,'nele=',nele
	write(*,*)' Programm has been started. '
	iii=4./(xs(2)-xs(1))
        call gettim(h_n,m_n,s_n,hs_n)
        call getdat(gd_n,md_n,dd_n)
        keles=ne(iii)
        do while(exited.and.keles.lt.nele)
          call lav()
          keles=ne(iii)
          write(*,17)keles,kele,char(13)
 17       format(' electron-->',i8,i6,a\)
          kele=kele+1
          if(kbhit().eq.255)then
	    if(getch().eq.27)exited=.false.
	  endif
        enddo
        call gettim(h_k,m_k,s_k,hs_k)
        call getdat(gd_k,md_k,dd_k)
        tn=dble(h_n)*3600.d0+dble(m_n)*60.d0+
     &    dble(s_n)+dble(hs_n)/100.d0
        tk=dble(h_k+(dd_k-dd_n)*24)*3600.d0+dble(m_k)*60.d0+
     &    dble(s_k)+dble(hs_k)/100.d0
        tr=tr+tk-tn
        ihh=idint(tr/3600.d0)
        tt1=tr-dble(ihh)*3600.d0
        minut=idint(tt1/60.d0)
        tt1=tt1-dble(minut)*60.d0
        sec=mod(sngl(tt1),60.)
	rewind 5
	INCLUDE 'write.fn'
	close(unit=5)
        write(*,*)  
        write(*,73)ihh,minut,sec
	open(15,file='rnd.tec')
	  write(15,*)rand
	close(15)
 73     format(' time=',i2.2,':',i2.2,':',f5.2)
        write(*,*)' ------------end--------------',char(7)
        end
