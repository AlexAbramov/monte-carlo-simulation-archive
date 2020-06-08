c
c		Основная программа.
с		Создание файла массивов сечений. 	
c
      include 'inits.fn'
      call rassech		! Подпрограмма расчета сечений.
      write(*,*)' Pion=',pion
      do i=1,nexp
	write(*,*)'Nex=',i,' Pexi=',pexi(i)
      enddo
      include 'write_se.fn'	!  Запись массивов сечений в файл.
      do i=1,nser
        write(*,*)i,stot(i),selas(i),sexi(nexp,i),sion(i)
      enddo
      end
