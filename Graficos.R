library(ggplot2)

tExec <- read.csv("resultados.csv")

ggplot(data = tExec, aes(x = troco))+
  geom_line(aes(y = naiveRecursivo, color = "red"))+
  geom_line(aes(y = algoritmoPD, color = "blue"))+
  scale_y_time(name = "Tempo de execução (s)")+
  scale_x_continuous(name = "Valor do troco")+
  theme_bw()
