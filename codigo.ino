// Identificação das portas
int ledVerde = 3;    // Pino do LED verde
int ledAmarelo = 4;   // Pino do LED amarelo
int ledVermelho = 2;  // Pino do LED vermelho
int buzzer = 5;     // Pino do buzzer
int LDR = A0;     // Pino do sensor LDR (sensor de luminosidade)

int analogValue;    // Variável para armazenar o valor lido do sensor LDR

bool apitando = false;

// Configurações iniciais
void setup() {
  pinMode(ledVerde,OUTPUT);   // Define o pino do LED verde como saída
  pinMode(ledAmarelo,OUTPUT); // Define o pino do LED amarelo como saída
  pinMode(ledVermelho,OUTPUT);  // Define o pino do LED vermelho como saída
  pinMode(LDR, INPUT);      // Define o pino do sensor LDR como entrada
  pinMode(buzzer,OUTPUT);   // Define o pino do buzzer como saída

  Serial.begin(9600);     // Inicializa a comunicação serial com taxa de transferência de 9600 bps
  
  digitalWrite(buzzer, HIGH); // Desliga o buzzer no início do programa
}

// Verificação do nível de luminosidade
void loop(){
  int temporario[10];     // Array temporário para armazenar valores de leitura do sensor LDR
  int soma = 0;         // Variável para armazenar a soma dos valores lidos do sensor LDR
  // Realiza 10 leituras do sensor LDR e soma os valores lidos
  for(int i = 0; i < 10; i++) {
    analogValue = analogRead(LDR);  // Realiza a leitura do sensor LDR
    soma += map(analogValue, 200, 1023, 0, 100); // Mapeia o valor lido para o intervalo de 0 a 100 e adiciona à soma  
  }

  int intensidade = soma / 10;    // Calcula a média das 10 leituras, representando a intensidade de luminosidade
  
 
  Serial.println(intensidade);    // Imprime a intensidade de luminosidade no monitor serial
  
  // Verifica a intensidade de luminosidade e ativa os LEDs e o buzzer de acordo com a necessidade
  if(intensidade < 40){  // Se a intensidade for menor que 60 (Baixa luminosidade - Ambiente adequado)
    digitalWrite(ledVerde, HIGH); // Acende o LED verde
    apitando = false;
  }
  else if(intensidade >= 40 && intensidade <= 80){  // Se a intensidade estiver entre 60 e 90 (Luminosidade em nível de alerta)
    digitalWrite(ledAmarelo, HIGH); // Acende o LED amarelo
    apitando = false;
  }
  else{   // Se a intensidade for maior que 90 (Alta luminosidade - Indicação de que há um problema)
    digitalWrite(ledVermelho, HIGH);// Acende o LED vermelho
    apitando = true;    // Liga o buzzer para indicar o problema
  }

  if (apitando == true) {
    for (int i=1; i<3; i++) {
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(200);
    }
  }
  
  delay(3000);
  digitalWrite(ledVerde, LOW);  // Aguarda 3 segundos antes de reiniciar o loop
  // Desliga todos os LEDs e o buzzer antes de reiniciar o loop
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(buzzer, HIGH);
}
