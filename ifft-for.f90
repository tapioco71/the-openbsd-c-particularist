! -*- mode: f90-mode; -*-

function idft(x, count)
  use, intrinsic : c_iso_binding
  implicit none
  logical(c_bool) :: idft
  integer(c_size_t), value :: count
  complex(c_double_complex), intent(in, out) :: x(1 : count)
  complex(c_double_complex) :: temp(1 : count), wn
  !
  idft = .false.
  if (count .gt. 0) then
     wn = exp((0.0, 1.0) * pi * 2.0 / count)
     do j = 1, count
        temp(j) = 0.0
        do k = 1, count
           temp(j) = temp(j) + wn ** (j * k)
        end do
        temp(j) = temp(j) / count
     end do
     idft = .true.
  end if
end function idft

! End of ifft-for.f90 file.
