! -*- mode: f90-mode; -*-

! hello2-for.f90 file.

subroutine hello(count)
  use, intrinsic :: iso_c_binding, only: c_int
  implicit none
  integer(c_int), value :: count
  print "('Hello, ', i3, ' worlds!')", count
end subroutine hello

! End of hello2-for.f90 file.
