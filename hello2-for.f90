! -*- mode: f90-mode; -*-

! hello2-for.f90 file.

module hello2

  use, intrinsic :: iso_c_binding, only: c_int
  implicit none

  interface

     subroutine hello(count) bind(C)
       use, intrinsic :: iso_c_binding, only: c_int
       implicit none
       integer(c_int), value :: count
     end subroutine hello

  end interface

end module hello2

subroutine hello(count)
  use, intrinsic :: iso_c_binding, only: c_int
  implicit none
  integer(c_int), value :: count
  print "('Hello, ', i3, ' worlds!')", count
end subroutine hello

! End of hello2-for.f90 file.
