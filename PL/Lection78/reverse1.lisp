(defun reverse1(s)
  (if (null s)
    s
    (append (reverse1 (cdr s)) (cons (car s) ()))
  )
)

(append (reverse1 (cdr s)) (car s)) //Будет ошибка, т.к. car s не список
