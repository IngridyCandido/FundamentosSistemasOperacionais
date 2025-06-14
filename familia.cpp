#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <signal.h>

using namespace std;

// Estrutura para representar cada membro da família
struct Membro {
    string nome;
    pid_t pid;
    int idade;
    bool vivo;
};

// Função para simular a vida de cada processo (filho)
void viver(string nome) {
    int idade = 0;
    while (idade <= 60) {
        sleep(1);
        idade++;

        if (idade == 60) {
            cout << nome << " (PID: " << getpid() << ") morreu aos 60 anos." << endl;
            exit(0);
        }
    }
}

int main() {
    vector<Membro> familia;

    pid_t pid_zezinho = -1, pid_huguinho = -1, pid_luizinho = -1;

    // Informações do Pai
    familia.push_back({"Papai", getpid(), 0, true});

    cout << "Papai nasceu (PID: " << getpid() << ")" << endl;

    while (true) {
        sleep(1);

        // Atualiza a idade de todos os membros vivos
        for (auto &m : familia) {
            if (m.vivo && m.idade < 60) {
                m.idade++;
            }
        }

        // Pega a idade atual do pai
        int idade_pai = 0;
        bool pai_vivo = true;
        for (auto &m : familia) {
            if (m.nome == "Papai") {
                idade_pai = m.idade;
                pai_vivo = m.vivo;
                break;
            }
        }

        // Verifica se é hora de ter filhos
        if (idade_pai == 20 && pid_zezinho == -1) {
            pid_zezinho = fork();
            if (pid_zezinho == 0) {
                viver("Zezinho");
            } else {
                familia.push_back({"Zezinho", pid_zezinho, 0, true});
                cout << "Zezinho nasceu aos 20 anos (PID: " << pid_zezinho << ")" << endl;
            }
        }

        if (idade_pai == 25 && pid_huguinho == -1) {
            pid_huguinho = fork();
            if (pid_huguinho == 0) {
                viver("Huguinho");
            } else {
                familia.push_back({"Huguinho", pid_huguinho, 0, true});
                cout << "Huguinho nasceu aos 25 anos (PID: " << pid_huguinho << ")" << endl;
            }
        }

        if (idade_pai == 30 && pid_luizinho == -1) {
            pid_luizinho = fork();
            if (pid_luizinho == 0) {
                viver("Luizinho");
            } else {
                familia.push_back({"Luizinho", pid_luizinho, 0, true});
                cout << "Luizinho nasceu aos 30 anos (PID: " << pid_luizinho << ")" << endl;
            }
        }

        // Verifica se algum filho morreu
        int status;
        pid_t pid_morto;
        while ((pid_morto = waitpid(-1, &status, WNOHANG)) > 0) {
            for (auto &m : familia) {
                if (m.pid == pid_morto) {
                    m.vivo = false;
                    cout << m.nome << " (PID: " << m.pid << ") morreu aos 60 anos." << endl;
                    break;
                }
            }
        }

        // Se o pai completou 60 anos, ele "morre"
        for (auto &m : familia) {
            if (m.nome == "Papai" && m.vivo && m.idade >= 60) {
                m.vivo = false;
                cout << "Papai (PID: " << m.pid << ") morreu aos 60 anos." << endl;
                break;
            }
        }

        // Exibe a situação da família após o nascimento do primeiro filho
        if (idade_pai >= 20) {
            cout << "\n===============================" << endl;
            cout << "Situação da Família (Ano " << idade_pai << ")" << endl;
            cout << "===============================" << endl;
            for (auto &m : familia) {
                cout << m.nome << " | PID: " << m.pid
                     << " | Idade: " << m.idade
                     << " | Status: " << (m.vivo ? "Vivo" : "Morto") << endl;
            }
            cout << "===============================\n" << endl;
        }

        // Verifica se todos morreram
        bool todos_mortos = true;
        for (auto &m : familia) {
            if (m.vivo) {
                todos_mortos = false;
                break;
            }
        }

        if (todos_mortos) {
            cout << "Todos os membros da família morreram. Encerrando programa." << endl;
            break;
        }
    }

    return 0;
}
