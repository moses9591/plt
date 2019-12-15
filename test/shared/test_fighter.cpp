
//#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Fighter.h"
//#include <./src/shared/state/Fighter.h>
#include "../../src/shared/state/State.h"
#include <boost/test/unit_test.hpp>

using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestExemple)
{
  {
	  /*
    Exemple ex {};
    BOOST_CHECK_EQUAL(ex.x, 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.x, 21);
    */
  }

  {
	  /*
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
    */
  }
}

BOOST_AUTO_TEST_CASE(TestConstructor)
{
  
  {//Thork
  // Fighter *fighter1;
	// fighter1->setName(Thork);
  // BOOST_CHECK_EQUAL(fighter1->getName(), Thork);
  

  // //Flint
  // Fighter fighter2 {};
	// fighter2.setName(Flint);
  // BOOST_CHECK_EQUAL(fighter2->getName(), Flint);
  

  // //Setting of HealthPointsMax
  // fighter1.setHealthPointsMax(100);
  // BOOST_CHECK_EQUAL(fighter1->getHealthPointsMax(), 100);
  // fighter2.setHealthPointsMax(100);
  // BOOST_CHECK_EQUAL(fighter2.getHealthPointsMax(), 100);

  //  //Setting of HealthPoints
  // fighter1.setHealthPoints(100);
  // BOOST_CHECK_EQUAL(fighter1.getHealthPoints(), 100);
  // fighter2.setHealthPoints(100);
  // BOOST_CHECK_EQUAL(fighter2.getHealthPoints(), 100);
  
  // //Setting of combo
  // fighter1.setCombo(5);
  // BOOST_CHECK_EQUAL(fighter1.getCombo(), 5);
  // fighter2.setCombo(5);
  // BOOST_CHECK_EQUAL(fighter2.getCombo(), 5);

  // //Setting of Status
  // fighter1.setStatus(DEAD);
  // BOOST_CHECK_EQUAL(fighter1.getStatus(), DEAD);
  // fighter2.setStatus(DEAD);
  // BOOST_CHECK_EQUAL(fighter2.getStatus(), DEAD);

  // //Fighting tests
  // fighter1.fight(fighter2, COUPDEPOING);
  // BOOST_CHECK_EQUAL(fighter1.getAttack(), COUPDEPOING);

  // BOOST_CHECK_LT(fighter2.getHealthPoints(), 100);
  // fighter1.fight(fighter2, COUPDEPIED);
  // BOOST_CHECK_EQUAL(fighter1.getAttack(), COUPDEPIED);

  // fighter1.fight(fighter2, FLASH_KICK);
  // BOOST_CHECK_EQUAL(fighter1.getAttack(), FLASH_KICK);

  // fighter1.fight(fighter2, UPPERCUT);
  // BOOST_CHECK_EQUAL(fighter1.getAttack(), UPPERCUT);
  // //checking HealthPoints equal to 0
  // BOOST_CHECK_EQUAL(fighter2.getHealthPoints(), 0);
  // //isDEAD fonction!!!

  // //Type of attack save in attacker's variable attack
  
  
  // //if fighter1 defends before fighter3's attack
  // Fighter fighter3 {};
	// fighter3.setName(Seku);
  // BOOST_CHECK_EQUAL(fighter3.getName(), Seku);
  
  // fighter1.setStatus(DEFENSE); // Thork in defense position
  // BOOST_CHECK_EQUAL(fighter1.getHealthPoints(),100);
  // fighter3.fight(fighter1,UPPERCUT); // Seku attacks
  // BOOST_CHECK_EQUAL(fighter1.getHealthPoints(),85);//checking if UPPERCUT 
  //                                                 //caused less damage :15

  // //Fighter fighter4 {};
  // Fighter fighter4(Kuro, 1,DEAD,100,100,10,0,COUPDEPOING,0);
  // BOOST_CHECK_EQUAL(fighter4.getName(),Kuro);
  // BOOST_CHECK_EQUAL(fighter4.getStatus(),DEAD);
  // BOOST_CHECK_EQUAL(fighter4.getHealthPointsMax(),100);
  // BOOST_CHECK_EQUAL(fighter4.getHealthPoints(),100);
  // //BOOST_CHECK_EQUAL(fighter4.getMovePoints(),10);
  // BOOST_CHECK_EQUAL(fighter4.getCombo(),0);
  // BOOST_CHECK_EQUAL(fighter4.getAttack(),COUPDEPOING);
  // //fighter1.defend(fighter3);



   //State
    {
      // State s {};
      // Fighter fighter1;
      // s.setFighter(fighter1);
      // s.getFighter();
    }
  }

    // testing of the second constructor
  // {
  //   Fighter fighter3(Thork,DEAD,100,100,10,COUPDEPOING);


  // }
}




/* vim: set sw=2 sts=2 et : */
