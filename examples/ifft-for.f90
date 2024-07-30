! -*- mode: f90-mode; -*-

function idft(x, count)
  use, intrinsic :: iso_c_binding
  implicit none
  logical(c_bool) :: idft
  integer(c_size_t), value :: count
  complex(c_double_complex), intent(out) :: x(1 : count)
  complex(c_double_complex) :: temp(1 : count), wn
  real(c_double), parameter :: pi = 2.0 * asin(1.0)
  integer :: j, k
  !
  idft = .false.
  if (count .gt. 0) then
     wn = exp(-2.0 * (0.0, 1.0) * pi / count)
     do j = 1, count
        temp(j) = (0.0, 0.0)
        do k = 1, count
           temp(j) = temp(j) + x(k) * wn ** ((j - 1) * (k - 1))
        end do
        temp(j) = temp(j) / count
     end do
     x(1 : count) = temp(1 : count)
     idft = .true.
  end if
end function idft

! End of ifft-for.f90 file.
