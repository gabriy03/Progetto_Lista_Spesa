//
// Created by gabriele on 08/01/26.
//

#ifndef PROGETTOLISTASPESA_UTENTE_H
#define PROGETTOLISTASPESA_UTENTE_H

#include <string>

class Utente {

public:

    Utente(const std::string& nomeUtente, const std::string& pass);

    std::string getNickname() const;

    std::string getPassword() const;

    // Metodo per il login (restituisce true se nick e pass sono corretti)
    bool login(const std::string& inputNick, const std::string& inputPass) const;


    void modificaPassword(const std::string& nuovaPass);


private:
    std::string nickname;
    std::string password;
};

#endif //PROGETTOLISTASPESA_UTENTE_H