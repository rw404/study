package main
import ("fmt"; "io/ioutil"; "os"; "strings")

func main() {
  rdr := os.Stdin
  b, err := ioutil.ReadAll(rdr) // Кортеж tuple
  if err != nil {
    panic("bad input") // Единственный способ отображения исключения
  }

  s := strings.Split(string(b), "") // ReadALL возвращает массив байтов; 
  // Делим строку на символы, чтобы обращаться по индексу к символам(UTF-8) 

  // Реверс
  for i, j:=0, len(s)-1; i<j; i,j=i+1, j-1 {
    s[i], s[j] = s[j], s[i]
  }

  // Вырезку из массива объединяем в строку
  fmt.Println(strings.Join(s, ""))
}
