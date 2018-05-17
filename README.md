# Konto-App
Example: 
```sh
First you have to choose a bank with
>change_bank
enter
><1-4>
now you have to create a person
>new_pers
enter a name for the person(its unique)
>Spliomix
you get the bank number from the new bank Account
```

now you can choose between some methods:
transfere money, make a withdrawal or deposit money...
Press <help> for more information
  
  
# Own Main Implementation

## Erstellen einer Person und 2 Konten für diese
```cpp
#include"Konto.h"
int main()
{
  std::shared_ptr<Bank>Raiffeisen(new Bank);    //neue Bank erstellen
  std::string spliomix_KNR1=Raiffeisen->neuerKunde("Spliomix"); //Kontonummer von Spliomix
  std::string spliomix_KNR2=Raiffeisen->neues_konto(*(Raiffeisen->get_kunde("Spliomix"))); //erstellt ein zweites Konto für Spliomix
}

```



  descriptions of the class methods are in the header files


