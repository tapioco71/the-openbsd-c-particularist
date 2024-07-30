! -*- mode: f90-mode; -*-

! mean-for.f90 file.


program meaning

  use, intrinsic :: iso_c_binding, only: c_size_t, c_double
  implicit none

  interface

     function mean(values, count) bind(C, name = "mean")
       use, intrinsic :: iso_c_binding, only: c_size_t, c_double
       implicit none
       real(c_double) :: mean
       integer(c_size_t), value :: count
       real(c_double) :: values(1,count)
     end function mean

  end interface

  integer(c_size_t), parameter :: count = 10
  real(c_double) :: values(count)
  !
  values(:) = (/1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0/)
  print "('The mean is ', f16.6)", mean(values, count)
  stop

end program meaning

! End of mean-for.f90 file.
