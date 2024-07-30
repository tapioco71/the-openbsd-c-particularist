! -*- mode: f90-mode; -*-

! norm2-for.f90 file.

function norm2(values, count)
  use, intrinsic :: iso_c_binding, only: c_size_t, c_double
  implicit none
  real(c_double) :: norm2
  real(c_double) :: r
  integer(c_size_t), value :: count
  real(c_double) :: values(1 : count)
  integer :: i
  !
  do i = 1, count
     if (i .eq. 1) then
        norm2 = values(1) ** 2.0
     else
        norm2 = norm2 + values(i) ** 2.0
     end if
  end do
  norm2 = sqrt(norm2)
end function norm2

! End of norm2-for.f90 file.
