! -*- mode: f90; -*-

! fft-for.f90 file.

program ffting

  use, intrinsic :: iso_c_binding
  implicit none

  interface

     function dft(x, count) bind(C, name = "dft")
       use, intrinsic :: iso_c_binding
       implicit none
       logical(c_bool) :: dft
       integer(c_size_t), value :: count
       complex(c_double_complex) :: x(1 : count)
     end function dft

  end interface

  integer(c_size_t), parameter :: count = 10
  complex(c_double_complex) :: x(1 : count)
  integer :: i
  !
  x = (/ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 /)
  if (dft(x, count) .eqv. .true.) then
     do i = 1, count
        print *, x(i)
     end do
  else
     print *, "Error computing the fft."
  end if

end program ffting

! End of fft-for.f90 file.
