 
  
# Own Main Implementation

## Erstellen einer Person und 2 Konten für diese
```cpp
#include"Konto.h"
int main()
{
  std::shared_ptr<Bank>Raiffeisen(new Bank);    //neue Bank erstellen
  std::string spliomix_KNR1=Raiffeisen->neuerKunde("Spliomix", false); //Kontonummer von Spliomix /false for Businneskonto
  std::string spliomix_KNR2=Raiffeisen->neues_konto(*(Raiffeisen->get_kunde("Spliomix")),true); //erstellt ein zweites Konto für Spliomix/true for Girokonto
  return 0;
}

```

## Einzahlen, Auszaheln und Kontotand von einem Konto
```cpp
  Raiffeisen->get_Konto(spliomix_KNR1)->einzahlen(1200);
  Raiffeisen->get_Konto(spliomix_KNR1)->auszahlen(200);
  Raiffeisen->get_Konto(spliomix_KNR1)->get_kontostand();
```

## Überweisen von einem Konto
```cpp
Raiffeisen->get_Konto(spliomix_KNR1)->ueberweisen(500, *(Raiffeisen->get_Konto(spliomix_KNR2)));
```

  descriptions of the class methods are in the header files


