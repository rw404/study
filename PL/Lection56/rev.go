package main
import ("fmt"; "io/ioutil"; "os";)

func main() {
  rdr := os.Stdin
  b, err := ioutil.ReadAll(rdr) // Кортеж tuple
  if err != nil {
    panic("bad input") // Единственный способ отображения исключения
  }

  s := string(b) // ReadALL возвращает массив байтов; 
  // Для строки нужно добавить, чтобы байты понимались с кодировкой UTF-8
  // Динамическая строка

  for i := len(s)-1; i>= 0; i-- {
    fmt.Print(s[i]) // Последовательность байтов
  }
}
