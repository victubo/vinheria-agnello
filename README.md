# Monitoramento Ambiental com Arduino

## Grupo:
* Glauco Heitor Gonçalves e Silva
* Lucas Himeno do Carmo
* Victor Hugo de Paula
* Otavio Santos de Lima Ferrao
* Gabriel Guilherme Leste


## Hardware Necessário

<ol>
<li>Arduino Uno (ou similar)</li>
<li>Sensor de temperatura e umidade DHT22 (ou DHT11)</li>
<li>Sensor de luminosidade</li>
<li>Display LCD 16x2</li>
<li>LEDs (vermelho, amarelo, verde)</li>
<li>Buzzer</li>
<li>Resistores e fios de conexão</li>
</ol>

## Bibliotecas Necessárias

- DHT (para o sensor DHT22)
- LiquidCrystal (para o display LCD)

## Instalação

1. Conecte os componentes conforme o esquema de ligação fornecido.
2. Faça o upload do código para o Arduino.
3. Certifique-se de instalar as bibliotecas necessárias.

## Como Usar

1. O Arduino começará a ler as informações ambientais assim que for ligado.
2. O display LCD mostrará a temperatura, umidade e luminosidade em tempo real.
3. LEDs e o buzzer serão acionados caso alguma das condições ambientais ultrapasse os limites definidos.
4. O código pode ser personalizado para ajustar os valores de alerta e aviso conforme necessário.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir problemas ou enviar solicitações de pull.

## Agradecimentos

Agradecemos ao professor Cabrini pelo suporte e orientação.

## FAQ

### P: Posso usar outro tipo de sensor de temperatura?
R: Sim, você pode modificar o código para usar outros sensores compatíveis com o Arduino.

### P: Como posso ajustar os limites de alerta?
R: Você pode alterar os valores das variáveis `lightAlert`, `humAlert` e `tempAlert` no código para ajustar os valores de alerta conforme necessário.

### P: Qual foi o método de leitura dos sensores utilizado?
R: Utilizamos uma média móvel de 10 leituras para evitar picos aleatórios e suavizar as variações entre as leituras.

## Suporte

Se você tiver dúvidas ou encontrar problemas, entre em contato através do email gabrielgleste@gmail.com.

## Roadmap

- Adicionar suporte para outros tipos de sensores de temperatura e umidade.
- Implementar uma interface de usuário mais interativa.
- Expandir os recursos de monitoramento para incluir mais parâmetros ambientais.

## Histórico de Versões

- **v2.0.0** (28/04/2024): Segunda versão do projeto.
