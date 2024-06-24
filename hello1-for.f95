! -*- mode: f90-mode; -*-

! hello1-for.f95 file.

  
program hello1
  
  use, intrinsic :: iso_c_binding, only: c_int
  implicit none
  
  interface
     subroutine hello(count) bind(C)
       use, intrinsic :: iso_c_binding, only: c_int
       implicit none
       integer(c_int), value :: count
     end subroutine hello
  end interface
  
  integer(c_int) :: x
  x = 10
  call hello(x)
  stop
  
end program hello1

! End of hello1-for.f95 file.
