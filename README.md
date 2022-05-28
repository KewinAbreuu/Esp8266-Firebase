# Esp8266-Firebase
</hr>

<p>Consiga automatizar dispositivos com o esp8266 e firebase<p>
  
## 🚀  Como usar! </hr>

Instale a Biblioteca contida em uma pasta nos arquivos iniciais:
```
 Pasta -->  Firebase_Arduino_Client_Library_for_ESP8266_and_ESP32
```

Abra o Arquivo Aduino :
```
  Arquivo --> TESTE
```
 
- [x] Coloque o Terminal em 115200
- [x] Vá em Ferramentas/MMU e Selecione 16kb cache + 48kb...


Edite as regras do realtimeDatabase :
```
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
```
Habilite o Modo anonimo na autenticação firebase

```
  Compile o código
```

