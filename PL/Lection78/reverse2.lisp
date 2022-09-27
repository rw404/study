(defun shift(l r)
  (if (null l)
     r
     (shift (cdr l) (cons (car l) r))
  )
)

(defun reverse1(s) (shift s nil))
