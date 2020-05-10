#include "malom.h"
#include <algorithm>
#include <numeric>

using namespace genv;
using namespace std;

Malom::Malom() : egyikJatekos(true)
{
    hatterrajzol(500);
    for (int i = 0; i < 9; i++)
    {
        Babu *b = new Babu(470,30+i*25,true);
        babuk.push_back(b);
        feltolt(b);

        b = new Babu(10,30+i*25,false);
        babuk.push_back(b);
        feltolt(b);
    }

    int a = 500;
    vector<float> aranyok = {0.1, 0.25, 0.4, 0.5, 0.6, 0.75, 0.9};
    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 7; y++)
        {
            if (tabla[x][y] == 0)
            {
                Csomopont *cs = new Csomopont(a*aranyok[x]-18, a*aranyok[y]-18, x, y, 
                    [=](int x, int y, Csomopont* c) { csomopont_visszajelzes(x, y, c); });
                    
                kattinthatok.push_back(cs);
                widgets.push_back(cs);
            }
        }
    }

    all_jelzo = new Allapotjelzo(250, 470, "rozsaszin rak");
    widgets.push_back(all_jelzo);

    Csomopont *cs;
    cs = csp_kereses(0, 0);
    cs->szomszed_hozzaad(csp_kereses(3, 0));
    cs->szomszed_hozzaad(csp_kereses(0, 3));

    cs = csp_kereses(3, 0);
    cs->szomszed_hozzaad(csp_kereses(6, 0));
    cs->szomszed_hozzaad(csp_kereses(3, 1));

    cs = csp_kereses(6, 0);
    cs->szomszed_hozzaad(csp_kereses(6, 3));

    cs = csp_kereses(1, 1);
    cs->szomszed_hozzaad(csp_kereses(3, 1));
    cs->szomszed_hozzaad(csp_kereses(1, 3));

    cs = csp_kereses(3, 1);
    cs->szomszed_hozzaad(csp_kereses(5, 1));
    cs->szomszed_hozzaad(csp_kereses(3, 2));

    cs = csp_kereses(5, 1);
    cs->szomszed_hozzaad(csp_kereses(5, 3));

    cs = csp_kereses(2, 2);
    cs->szomszed_hozzaad(csp_kereses(3, 2));
    cs->szomszed_hozzaad(csp_kereses(2, 3));

    cs = csp_kereses(3, 2);
    cs->szomszed_hozzaad(csp_kereses(4, 2));

    cs = csp_kereses(0, 3);
    cs->szomszed_hozzaad(csp_kereses(0, 6));
    cs->szomszed_hozzaad(csp_kereses(1, 3));

    cs = csp_kereses(1, 3);
    cs->szomszed_hozzaad(csp_kereses(1, 5));
    cs->szomszed_hozzaad(csp_kereses(2, 3));

    cs = csp_kereses(2, 3);
    cs->szomszed_hozzaad(csp_kereses(2, 4));

    cs = csp_kereses(4, 3);
    cs->szomszed_hozzaad(csp_kereses(5, 3));
    cs->szomszed_hozzaad(csp_kereses(4, 4));
    cs->szomszed_hozzaad(csp_kereses(4, 2));

    cs = csp_kereses(5, 2);
    cs->szomszed_hozzaad(csp_kereses(5, 3));

    cs = csp_kereses(5, 3);
    cs->szomszed_hozzaad(csp_kereses(6, 3));
    cs->szomszed_hozzaad(csp_kereses(5, 5));

    cs = csp_kereses(6, 3);
    cs->szomszed_hozzaad(csp_kereses(6, 6));

    cs = csp_kereses(2, 4);
    cs->szomszed_hozzaad(csp_kereses(3, 4));

    cs = csp_kereses(3, 4);
    cs->szomszed_hozzaad(csp_kereses(4, 4));
    cs->szomszed_hozzaad(csp_kereses(3, 5));

    cs = csp_kereses(1, 5);
    cs->szomszed_hozzaad(csp_kereses(3, 5));

    cs = csp_kereses(3, 5);
    cs->szomszed_hozzaad(csp_kereses(3, 6));
    cs->szomszed_hozzaad(csp_kereses(5, 5));

    cs = csp_kereses(3, 6);
    cs->szomszed_hozzaad(csp_kereses(6, 6));
    cs->szomszed_hozzaad(csp_kereses(0, 6));
}

Babu* Malom::jatekon_kivuli_babu()
{   
    auto talalat = std::find_if(babuk.begin(), babuk.end(), [=](Babu *b)
    {
        return b->ove_e(egyikJatekos) && !b->jatekban_e();
    });

    if (talalat != babuk.end())
    {
        return *talalat;
    }
    else
    {
        return nullptr;
    }
}

void Malom::ujra()
{
    egyikJatekos = true;
    int c_egyik = 0;
    int c_masik = 0;
    for (Babu *&b : babuk)
    {
        bool egyike = b->ove_e(egyikJatekos);
        b->kiut();
        if (egyike)
        {
            b->mozgat(470, 30 + c_egyik*25, -1, -1);
            c_egyik++;
        }
        else
        {
            b->mozgat(10, 30 + c_masik*25, -1, -1);
            c_masik++;
        }
    }
    for (vector<int> &sor : tabla)
    {
        for (int &cella : sor)
        {
            if (cella != -1)
            {
                cella = 0;
            }
        }
    }
    allapot = felrakas;
    all_jelzo->set_szoveg("rozsaszin rak");
}

int Malom::babuk_jatekban(bool egyik)
{
    int db = std::count_if(babuk.begin(), babuk.end(), [egyik](Babu *b)
    {
        return b->ove_e(egyik) && b->jatekban_e();
    });
    return db;
}

void Malom::csomopont_visszajelzes(int x, int y, Csomopont *cs)
{
    int a = 500;
    vector<float> aranyok = {0.1, 0.25, 0.4, 0.5, 0.6, 0.75, 0.9};

    if (allapot == felrakas)
    {
        if (babuk_jatekban(true) < babuk_szama || babuk_jatekban(false) < babuk_szama)
        {
            Babu *b = jatekon_kivuli_babu();
            if (tabla[x][y] == 0)
            {
                if (egyikJatekos)
                {
                    tabla[x][y] = 1;
                    all_jelzo->set_szoveg("kek rak");
                }
                else
                {
                    tabla[x][y] = 2;
                    all_jelzo->set_szoveg("rozsaszin rak");
                }
                b->mozgat(a*aranyok[x]-10, a*aranyok[y]-10, x, y);
                b->jatekba_helyez();
                egyikJatekos = !egyikJatekos;

                if (babuk_jatekban(false) == babuk_szama)
                {
                    all_jelzo->set_szoveg("rozsaszin valaszt");  
                }
            }
        }
        else
        {
            allapot = kivalasztas;
        }
    }

    if (allapot == utes)
    {
        bool utes = (egyikJatekos && tabla[x][y] == 2) || (!egyikJatekos && tabla[x][y] == 1);
        if (utes)
        {
            Babu *b = babu_kereses(x, y);
            b->mozgat(10 + 460*egyikJatekos, 30+babuk_jatekban(!egyikJatekos)*25, -1, -1);
            b->kiut();
            tabla[x][y] = 0;
            egyikJatekos = !egyikJatekos;
            allapot = kivalasztas;

            if (egyikJatekos)
            {
                all_jelzo->set_szoveg("rozsaszin valaszt");
            }
            else
            {
                all_jelzo->set_szoveg("kek valaszt");
            }
        }
    }

    if (allapot == mozgatas)
    {
        int kival_x = kivalasztott_csp->get_kx();
        int kival_y = kivalasztott_csp->get_ky();

        if (kivalasztott_csp->szomszedja_e(cs) && tabla[x][y] == 0)
        {
            tabla[kival_x][kival_y] = 0;
            if (egyikJatekos)
            {
                tabla[x][y] = 1;
            }
            else
            {
                tabla[x][y] = 2;
            }
            babu_kereses(kival_x, kival_y)->mozgat(a*aranyok[x]-10, a*aranyok[y]-10, x, y);
            
            if (malom_e(x, y))
            {
                if (egyikJatekos)
                {
                    all_jelzo->set_szoveg("MALOM VAN! - uss le egy kek babut");
                }
                else
                {
                    all_jelzo->set_szoveg("MALOM VAN! - uss le egy rozsaszin babut");
                }
                allapot = utes;
            }
            else
            {
                allapot = kivalasztas;
                egyikJatekos = !egyikJatekos;
            }
        }
    }

    if(allapot == kivalasztas && tabla[x][y] != 0)    
    {
        if (egyikJatekos)
        {
            all_jelzo->set_szoveg("rozsaszin valaszt");
        }
        else
        {
            all_jelzo->set_szoveg("kek valaszt");
        }

        if((egyikJatekos && tabla[x][y] == 1) || (!egyikJatekos && tabla[x][y] == 2))
        {
            bool lephet = false;
            for (Csomopont *c : cs->get_szomszedok())
            {
                if(tabla[c->get_kx()][c->get_ky()] == 0)
                {
                    lephet = true;
                    break;
                }
            }
            
            kivalasztott_csp = cs;
            if (lephet)
            {
                allapot = mozgatas;
                if (egyikJatekos)
                {
                    all_jelzo->set_szoveg("rozsaszin mozgat");
                }
                else
                {
                    all_jelzo->set_szoveg("kek mozgat");
                }
            }
            else
            {
                all_jelzo->set_szoveg("kivalasztott babu nem lephet, probald masikkal");
            }
        }   
    }  

    if (allapot != felrakas)
    {
        if (babuk_jatekban(true) < 3)
        {
            all_jelzo->set_szoveg("kek nyert - nyomj ENTER-t az ujrakezdeshez");
            allapot = vege;
        }

        if (babuk_jatekban(false) < 3)
        {
            all_jelzo->set_szoveg("rozsaszin nyert - nyomj ENTER-t az ujrakezdeshez");
            allapot = vege;
        }
    }
}

Csomopont* Malom::csp_kereses(int x, int y)
{
    auto talalat = std::find_if(kattinthatok.begin(), kattinthatok.end(), [=](Csomopont *b)
    {
        return b->get_kx() == x && b->get_ky() == y;
    });

    return *talalat;
}

bool Malom::tud_e_mozogni(int x, int y)
{
    return false;
}
int Malom::osszeg(int x, int y, bool sor)
{
    int a, b;
    if (sor)
    {
        a = y;
        b = x;
    }
    else
    {
        a = x;
        b = y;
    }

    int mettol, meddig;
    if (a != 3)
    {
        mettol = 0;
        meddig = 7;
    } 
    else
    {
        if (b < 3)
        {
            mettol = 0;
            meddig = 3;
        }
        else
        {
            mettol = 4;
            meddig = 7;
        }
    }

    int ossz = 0;
    int mit = 1;
    if (!egyikJatekos) mit = 2;

    if (sor)
    {
        for (int i = mettol; i < meddig; i++)
        {
            ossz += (tabla[i][y] == mit);
        }
    }
    else
    {
        for (int i = mettol; i < meddig; i++)
        {
            ossz += (tabla[x][i] == mit);
        }
    }
    return ossz;
}
bool Malom::malom_e(int x, int y)
{
    int sor_ossz = osszeg(x, y, true);
    int oszlop_ossz = osszeg(x, y, false);

    return sor_ossz == 3 || oszlop_ossz == 3;
}
Babu* Malom::babu_kereses(int x, int y)
{
    auto talalat = std::find_if(babuk.begin(), babuk.end(), [=](Babu *b)
    {
        return b->get_kx() == x && b->get_ky() == y;
    });

    return *talalat;
}

void Malom::hatterrajzol(int a)
{
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    int betolas = a*0.1;
    int hossz = a*0.8;
    hatter << move_to(betolas,betolas) << box(hossz, 5) << box(-5,hossz) << box(-hossz,-5) << box(5, -hossz);
    
    betolas = a*0.25;
    hossz = a*0.5;
    hatter << move_to(betolas,betolas) << box(hossz, 5) << box(-5,hossz) << box(-hossz,-5) << box(5, -hossz);

    betolas = a*0.4;
    hossz = a*0.2;
    hatter << move_to(betolas,betolas) << box(hossz, 5) << box(-5,hossz) << box(-hossz,-5) << box(5, -hossz);

    betolas = a*0.1;
    hossz = a*0.3;
    hatter << move_to(a*0.5-2,betolas) << box(5, hossz) 
           << move_to(a*0.5-2,a-betolas) << box(5,-hossz)
           << move_to(a-betolas-5,a*0.5-2) << box(-hossz, 5)
           << move_to(betolas,a*0.5-2) << box(hossz, 5); 
}


void Malom::handle()
{
    gout << stamp(hatter,0,0);

    for(Widget *w : widgets)
    {
        w->kirajzol();
    }
    gout << refresh;

    event ev;
    Widget *focus=nullptr;
    while(gin >> ev)
    {
        for(Widget *w : widgets)
        {
            if(w->folotte(ev.pos_x, ev.pos_y))
            {
                if(ev.button == btn_left)
                {
                    focus=w;
                }
            }
        }
        if (focus)
        {
            focus->kezel(ev);
        }
        gout << stamp(hatter, 0, 0);
        for (Widget *w : widgets)
        {
            w->kirajzol();
        }

        gout << color(255, 0 ,0);
        for (Csomopont *cs : kattinthatok)
        {
            cs->kirajzol();
        }

        if (ev.keycode == key_enter && allapot == vege)
        {
            ujra();
        }
        gout << refresh;
    }
}

void Malom::futtatas()
{
    gout.open(500, 500);
    handle();
}