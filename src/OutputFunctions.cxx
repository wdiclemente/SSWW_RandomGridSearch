#include "Train.h"
#include <utility>
#include <cmath>

void Train::FillTree(std::map<int, std::pair<double, double> > seen_map, std::map<int, std::pair<double, double> > pass_map) {
  // map is structured as:
  //   - key          = run number
  //   - value.first  = events passing criteria
  //   - value.second = error squared

  float temp_seen = 0;

  count_999999 = pass_map[999999].first;
  error_999999 = pass_map[999999].second;
  temp_seen = seen_map[999999].first;
  fraction_999999 = (temp_seen != 0 ? count_999999/temp_seen : 0.0);

  count_111111 = pass_map[111111].first;
  error_111111 = pass_map[111111].second;
  temp_seen = seen_map[111111].first;
  fraction_111111 = (temp_seen != 0 ? count_111111/temp_seen : 0.0);

  count_222222 = pass_map[222222].first;
  error_222222 = pass_map[222222].second;
  temp_seen = seen_map[222222].first;
  fraction_222222 = (temp_seen != 0 ? count_222222/temp_seen : 0.0);

  count_990031 = pass_map[990031].first;
  error_990031 = pass_map[990031].second;
  temp_seen = seen_map[990031].first;
  fraction_990031 = (temp_seen != 0 ? count_990031/temp_seen : 0.0);

  count_123456 = pass_map[123456].first;
  error_123456 = pass_map[123456].second;
  temp_seen = seen_map[123456].first;
  fraction_123456 = (temp_seen != 0 ? count_123456/temp_seen : 0.0);

  count_364284 = pass_map[364284].first;
  error_364284 = pass_map[364284].second;
  temp_seen = seen_map[364284].first;
  fraction_364284 = (temp_seen != 0 ? count_364284/temp_seen : 0.0);

  count_364250 = pass_map[364250].first;
  error_364250 = pass_map[364250].second;
  temp_seen = seen_map[364250].first;
  fraction_364250 = (temp_seen != 0 ? count_364250/temp_seen : 0.0);

  count_364254 = pass_map[364254].first;
  error_364254 = pass_map[364254].second;
  temp_seen = seen_map[364254].first;
  fraction_364254 = (temp_seen != 0 ? count_364254/temp_seen : 0.0);

  count_364255 = pass_map[364255].first;
  error_364255 = pass_map[364255].second;
  temp_seen = seen_map[364255].first;
  fraction_364255 = (temp_seen != 0 ? count_364255/temp_seen : 0.0);

  count_363718 = pass_map[363718].first;
  error_363718 = pass_map[363718].second;
  temp_seen = seen_map[363718].first;
  fraction_363718 = (temp_seen != 0 ? count_363718/temp_seen : 0.0);

  count_363719 = pass_map[363719].first;
  error_363719 = pass_map[363719].second;
  temp_seen = seen_map[363719].first;
  fraction_363719 = (temp_seen != 0 ? count_363719/temp_seen : 0.0);

  count_364242 = pass_map[364242].first;
  error_364242 = pass_map[364242].second;
  temp_seen = seen_map[364242].first;
  fraction_364242 = (temp_seen != 0 ? count_364242/temp_seen : 0.0);

  count_364243 = pass_map[364243].first;
  error_364243 = pass_map[364243].second;
  temp_seen = seen_map[364243].first;
  fraction_364243 = (temp_seen != 0 ? count_364243/temp_seen : 0.0);

  count_364244 = pass_map[364244].first;
  error_364244 = pass_map[364244].second;
  temp_seen = seen_map[364244].first;
  fraction_364244 = (temp_seen != 0 ? count_364244/temp_seen : 0.0);

  count_364245 = pass_map[364245].first;
  error_364245 = pass_map[364245].second;
  temp_seen = seen_map[364245].first;
  fraction_364245 = (temp_seen != 0 ? count_364245/temp_seen : 0.0);

  count_364246 = pass_map[364246].first;
  error_364246 = pass_map[364246].second;
  temp_seen = seen_map[364246].first;
  fraction_364246 = (temp_seen != 0 ? count_364246/temp_seen : 0.0);

  count_364336 = pass_map[364336].first;
  error_364336 = pass_map[364336].second;
  temp_seen = seen_map[364336].first;
  fraction_364336 = (temp_seen != 0 ? count_364336/temp_seen : 0.0);

  count_364337 = pass_map[364337].first;
  error_364337 = pass_map[364337].second;
  temp_seen = seen_map[364337].first;
  fraction_364337 = (temp_seen != 0 ? count_364337/temp_seen : 0.0);

  count_364338 = pass_map[364338].first;
  error_364338 = pass_map[364338].second;
  temp_seen = seen_map[364338].first;
  fraction_364338 = (temp_seen != 0 ? count_364338/temp_seen : 0.0);

  count_364339 = pass_map[364339].first;
  error_364339 = pass_map[364339].second;
  temp_seen = seen_map[364339].first;
  fraction_364339 = (temp_seen != 0 ? count_364339/temp_seen : 0.0);

  count_363507 = pass_map[363507].first;
  error_363507 = pass_map[363507].second;
  temp_seen = seen_map[363507].first;
  fraction_363507 = (temp_seen != 0 ? count_363507/temp_seen : 0.0);

  count_363508 = pass_map[363508].first;
  error_363508 = pass_map[363508].second;
  temp_seen = seen_map[363508].first;
  fraction_363508 = (temp_seen != 0 ? count_363508/temp_seen : 0.0);

  count_363509 = pass_map[363509].first;
  error_363509 = pass_map[363509].second;
  temp_seen = seen_map[363509].first;
  fraction_363509 = (temp_seen != 0 ? count_363509/temp_seen : 0.0);

  count_410155 = pass_map[410155].first;
  error_410155 = pass_map[410155].second;
  temp_seen = seen_map[410155].first;
  fraction_410155 = (temp_seen != 0 ? count_410155/temp_seen : 0.0);

  count_410218 = pass_map[410218].first;
  error_410218 = pass_map[410218].second;
  temp_seen = seen_map[410218].first;
  fraction_410218 = (temp_seen != 0 ? count_410218/temp_seen : 0.0);

  count_410219 = pass_map[410219].first;
  error_410219 = pass_map[410219].second;
  temp_seen = seen_map[410219].first;
  fraction_410219 = (temp_seen != 0 ? count_410219/temp_seen : 0.0);

  count_410220 = pass_map[410220].first;
  error_410220 = pass_map[410220].second;
  temp_seen = seen_map[410220].first;
  fraction_410220 = (temp_seen != 0 ? count_410220/temp_seen : 0.0);

  count_410642 = pass_map[410642].first;
  error_410642 = pass_map[410642].second;
  temp_seen = seen_map[410642].first;
  fraction_410642 = (temp_seen != 0 ? count_410642/temp_seen : 0.0);

  count_410643 = pass_map[410643].first;
  error_410643 = pass_map[410643].second;
  temp_seen = seen_map[410643].first;
  fraction_410643 = (temp_seen != 0 ? count_410643/temp_seen : 0.0);

  count_410644 = pass_map[410644].first;
  error_410644 = pass_map[410644].second;
  temp_seen = seen_map[410644].first;
  fraction_410644 = (temp_seen != 0 ? count_410644/temp_seen : 0.0);

  count_410645 = pass_map[410645].first;
  error_410645 = pass_map[410645].second;
  temp_seen = seen_map[410645].first;
  fraction_410645 = (temp_seen != 0 ? count_410645/temp_seen : 0.0);

  count_410501 = pass_map[410501].first;
  error_410501 = pass_map[410501].second;
  temp_seen = seen_map[410501].first;
  fraction_410501 = (temp_seen != 0 ? count_410501/temp_seen : 0.0);

  count_147806 = pass_map[147806].first;
  error_147806 = pass_map[147806].second;
  temp_seen = seen_map[147806].first;
  fraction_147806 = (temp_seen != 0 ? count_147806/temp_seen : 0.0);

  count_147807 = pass_map[147807].first;
  error_147807 = pass_map[147807].second;
  temp_seen = seen_map[147807].first;
  fraction_147807 = (temp_seen != 0 ? count_147807/temp_seen : 0.0);

  count_363600 = pass_map[363600].first;
  error_363600 = pass_map[363600].second;
  temp_seen = seen_map[363600].first;
  fraction_363600 = (temp_seen != 0 ? count_363600/temp_seen : 0.0);

  count_363601 = pass_map[363601].first;
  error_363601 = pass_map[363601].second;
  temp_seen = seen_map[363601].first;
  fraction_363601 = (temp_seen != 0 ? count_363601/temp_seen : 0.0);

  count_363602 = pass_map[363602].first;
  error_363602 = pass_map[363602].second;
  temp_seen = seen_map[363602].first;
  fraction_363602 = (temp_seen != 0 ? count_363602/temp_seen : 0.0);

  count_363603 = pass_map[363603].first;
  error_363603 = pass_map[363603].second;
  temp_seen = seen_map[363603].first;
  fraction_363603 = (temp_seen != 0 ? count_363603/temp_seen : 0.0);

  count_363604 = pass_map[363604].first;
  error_363604 = pass_map[363604].second;
  temp_seen = seen_map[363604].first;
  fraction_363604 = (temp_seen != 0 ? count_363604/temp_seen : 0.0);

  count_363605 = pass_map[363605].first;
  error_363605 = pass_map[363605].second;
  temp_seen = seen_map[363605].first;
  fraction_363605 = (temp_seen != 0 ? count_363605/temp_seen : 0.0);

  count_363606 = pass_map[363606].first;
  error_363606 = pass_map[363606].second;
  temp_seen = seen_map[363606].first;
  fraction_363606 = (temp_seen != 0 ? count_363606/temp_seen : 0.0);

  count_363607 = pass_map[363607].first;
  error_363607 = pass_map[363607].second;
  temp_seen = seen_map[363607].first;
  fraction_363607 = (temp_seen != 0 ? count_363607/temp_seen : 0.0);

  count_363608 = pass_map[363608].first;
  error_363608 = pass_map[363608].second;
  temp_seen = seen_map[363608].first;
  fraction_363608 = (temp_seen != 0 ? count_363608/temp_seen : 0.0);

  count_363609 = pass_map[363609].first;
  error_363609 = pass_map[363609].second;
  temp_seen = seen_map[363609].first;
  fraction_363609 = (temp_seen != 0 ? count_363609/temp_seen : 0.0);

  count_363610 = pass_map[363610].first;
  error_363610 = pass_map[363610].second;
  temp_seen = seen_map[363610].first;
  fraction_363610 = (temp_seen != 0 ? count_363610/temp_seen : 0.0);

  count_363611 = pass_map[363611].first;
  error_363611 = pass_map[363611].second;
  temp_seen = seen_map[363611].first;
  fraction_363611 = (temp_seen != 0 ? count_363611/temp_seen : 0.0);

  count_363612 = pass_map[363612].first;
  error_363612 = pass_map[363612].second;
  temp_seen = seen_map[363612].first;
  fraction_363612 = (temp_seen != 0 ? count_363612/temp_seen : 0.0);

  count_363613 = pass_map[363613].first;
  error_363613 = pass_map[363613].second;
  temp_seen = seen_map[363613].first;
  fraction_363613 = (temp_seen != 0 ? count_363613/temp_seen : 0.0);

  count_363614 = pass_map[363614].first;
  error_363614 = pass_map[363614].second;
  temp_seen = seen_map[363614].first;
  fraction_363614 = (temp_seen != 0 ? count_363614/temp_seen : 0.0);

  count_363615 = pass_map[363615].first;
  error_363615 = pass_map[363615].second;
  temp_seen = seen_map[363615].first;
  fraction_363615 = (temp_seen != 0 ? count_363615/temp_seen : 0.0);

  count_363616 = pass_map[363616].first;
  error_363616 = pass_map[363616].second;
  temp_seen = seen_map[363616].first;
  fraction_363616 = (temp_seen != 0 ? count_363616/temp_seen : 0.0);

  count_363617 = pass_map[363617].first;
  error_363617 = pass_map[363617].second;
  temp_seen = seen_map[363617].first;
  fraction_363617 = (temp_seen != 0 ? count_363617/temp_seen : 0.0);

  count_363618 = pass_map[363618].first;
  error_363618 = pass_map[363618].second;
  temp_seen = seen_map[363618].first;
  fraction_363618 = (temp_seen != 0 ? count_363618/temp_seen : 0.0);

  count_363619 = pass_map[363619].first;
  error_363619 = pass_map[363619].second;
  temp_seen = seen_map[363619].first;
  fraction_363619 = (temp_seen != 0 ? count_363619/temp_seen : 0.0);

  count_363620 = pass_map[363620].first;
  error_363620 = pass_map[363620].second;
  temp_seen = seen_map[363620].first;
  fraction_363620 = (temp_seen != 0 ? count_363620/temp_seen : 0.0);

  count_363621 = pass_map[363621].first;
  error_363621 = pass_map[363621].second;
  temp_seen = seen_map[363621].first;
  fraction_363621 = (temp_seen != 0 ? count_363621/temp_seen : 0.0);

  count_363622 = pass_map[363622].first;
  error_363622 = pass_map[363622].second;
  temp_seen = seen_map[363622].first;
  fraction_363622 = (temp_seen != 0 ? count_363622/temp_seen : 0.0);

  count_363623 = pass_map[363623].first;
  error_363623 = pass_map[363623].second;
  temp_seen = seen_map[363623].first;
  fraction_363623 = (temp_seen != 0 ? count_363623/temp_seen : 0.0);

  count_363624 = pass_map[363624].first;
  error_363624 = pass_map[363624].second;
  temp_seen = seen_map[363624].first;
  fraction_363624 = (temp_seen != 0 ? count_363624/temp_seen : 0.0);

  count_363625 = pass_map[363625].first;
  error_363625 = pass_map[363625].second;
  temp_seen = seen_map[363625].first;
  fraction_363625 = (temp_seen != 0 ? count_363625/temp_seen : 0.0);

  count_363626 = pass_map[363626].first;
  error_363626 = pass_map[363626].second;
  temp_seen = seen_map[363626].first;
  fraction_363626 = (temp_seen != 0 ? count_363626/temp_seen : 0.0);

  count_363627 = pass_map[363627].first;
  error_363627 = pass_map[363627].second;
  temp_seen = seen_map[363627].first;
  fraction_363627 = (temp_seen != 0 ? count_363627/temp_seen : 0.0);

  count_363628 = pass_map[363628].first;
  error_363628 = pass_map[363628].second;
  temp_seen = seen_map[363628].first;
  fraction_363628 = (temp_seen != 0 ? count_363628/temp_seen : 0.0);

  count_363629 = pass_map[363629].first;
  error_363629 = pass_map[363629].second;
  temp_seen = seen_map[363629].first;
  fraction_363629 = (temp_seen != 0 ? count_363629/temp_seen : 0.0);

  count_363630 = pass_map[363630].first;
  error_363630 = pass_map[363630].second;
  temp_seen = seen_map[363630].first;
  fraction_363630 = (temp_seen != 0 ? count_363630/temp_seen : 0.0);

  count_363631 = pass_map[363631].first;
  error_363631 = pass_map[363631].second;
  temp_seen = seen_map[363631].first;
  fraction_363631 = (temp_seen != 0 ? count_363631/temp_seen : 0.0);

  count_363632 = pass_map[363632].first;
  error_363632 = pass_map[363632].second;
  temp_seen = seen_map[363632].first;
  fraction_363632 = (temp_seen != 0 ? count_363632/temp_seen : 0.0);

  count_363633 = pass_map[363633].first;
  error_363633 = pass_map[363633].second;
  temp_seen = seen_map[363633].first;
  fraction_363633 = (temp_seen != 0 ? count_363633/temp_seen : 0.0);

  count_363634 = pass_map[363634].first;
  error_363634 = pass_map[363634].second;
  temp_seen = seen_map[363634].first;
  fraction_363634 = (temp_seen != 0 ? count_363634/temp_seen : 0.0);

  count_363635 = pass_map[363635].first;
  error_363635 = pass_map[363635].second;
  temp_seen = seen_map[363635].first;
  fraction_363635 = (temp_seen != 0 ? count_363635/temp_seen : 0.0);

  count_363636 = pass_map[363636].first;
  error_363636 = pass_map[363636].second;
  temp_seen = seen_map[363636].first;
  fraction_363636 = (temp_seen != 0 ? count_363636/temp_seen : 0.0);

  count_363637 = pass_map[363637].first;
  error_363637 = pass_map[363637].second;
  temp_seen = seen_map[363637].first;
  fraction_363637 = (temp_seen != 0 ? count_363637/temp_seen : 0.0);

  count_363638 = pass_map[363638].first;
  error_363638 = pass_map[363638].second;
  temp_seen = seen_map[363638].first;
  fraction_363638 = (temp_seen != 0 ? count_363638/temp_seen : 0.0);

  count_363639 = pass_map[363639].first;
  error_363639 = pass_map[363639].second;
  temp_seen = seen_map[363639].first;
  fraction_363639 = (temp_seen != 0 ? count_363639/temp_seen : 0.0);

  count_363640 = pass_map[363640].first;
  error_363640 = pass_map[363640].second;
  temp_seen = seen_map[363640].first;
  fraction_363640 = (temp_seen != 0 ? count_363640/temp_seen : 0.0);

  count_363641 = pass_map[363641].first;
  error_363641 = pass_map[363641].second;
  temp_seen = seen_map[363641].first;
  fraction_363641 = (temp_seen != 0 ? count_363641/temp_seen : 0.0);

  count_363642 = pass_map[363642].first;
  error_363642 = pass_map[363642].second;
  temp_seen = seen_map[363642].first;
  fraction_363642 = (temp_seen != 0 ? count_363642/temp_seen : 0.0);

  count_363643 = pass_map[363643].first;
  error_363643 = pass_map[363643].second;
  temp_seen = seen_map[363643].first;
  fraction_363643 = (temp_seen != 0 ? count_363643/temp_seen : 0.0);

  count_363644 = pass_map[363644].first;
  error_363644 = pass_map[363644].second;
  temp_seen = seen_map[363644].first;
  fraction_363644 = (temp_seen != 0 ? count_363644/temp_seen : 0.0);

  count_363645 = pass_map[363645].first;
  error_363645 = pass_map[363645].second;
  temp_seen = seen_map[363645].first;
  fraction_363645 = (temp_seen != 0 ? count_363645/temp_seen : 0.0);

  count_363646 = pass_map[363646].first;
  error_363646 = pass_map[363646].second;
  temp_seen = seen_map[363646].first;
  fraction_363646 = (temp_seen != 0 ? count_363646/temp_seen : 0.0);

  count_363647 = pass_map[363647].first;
  error_363647 = pass_map[363647].second;
  temp_seen = seen_map[363647].first;
  fraction_363647 = (temp_seen != 0 ? count_363647/temp_seen : 0.0);

  count_363648 = pass_map[363648].first;
  error_363648 = pass_map[363648].second;
  temp_seen = seen_map[363648].first;
  fraction_363648 = (temp_seen != 0 ? count_363648/temp_seen : 0.0);

  count_363649 = pass_map[363649].first;
  error_363649 = pass_map[363649].second;
  temp_seen = seen_map[363649].first;
  fraction_363649 = (temp_seen != 0 ? count_363649/temp_seen : 0.0);

  count_363650 = pass_map[363650].first;
  error_363650 = pass_map[363650].second;
  temp_seen = seen_map[363650].first;
  fraction_363650 = (temp_seen != 0 ? count_363650/temp_seen : 0.0);

  count_363651 = pass_map[363651].first;
  error_363651 = pass_map[363651].second;
  temp_seen = seen_map[363651].first;
  fraction_363651 = (temp_seen != 0 ? count_363651/temp_seen : 0.0);

  count_363652 = pass_map[363652].first;
  error_363652 = pass_map[363652].second;
  temp_seen = seen_map[363652].first;
  fraction_363652 = (temp_seen != 0 ? count_363652/temp_seen : 0.0);

  count_363653 = pass_map[363653].first;
  error_363653 = pass_map[363653].second;
  temp_seen = seen_map[363653].first;
  fraction_363653 = (temp_seen != 0 ? count_363653/temp_seen : 0.0);

  count_363654 = pass_map[363654].first;
  error_363654 = pass_map[363654].second;
  temp_seen = seen_map[363654].first;
  fraction_363654 = (temp_seen != 0 ? count_363654/temp_seen : 0.0);

  count_363655 = pass_map[363655].first;
  error_363655 = pass_map[363655].second;
  temp_seen = seen_map[363655].first;
  fraction_363655 = (temp_seen != 0 ? count_363655/temp_seen : 0.0);

  count_363656 = pass_map[363656].first;
  error_363656 = pass_map[363656].second;
  temp_seen = seen_map[363656].first;
  fraction_363656 = (temp_seen != 0 ? count_363656/temp_seen : 0.0);

  count_363657 = pass_map[363657].first;
  error_363657 = pass_map[363657].second;
  temp_seen = seen_map[363657].first;
  fraction_363657 = (temp_seen != 0 ? count_363657/temp_seen : 0.0);

  count_363658 = pass_map[363658].first;
  error_363658 = pass_map[363658].second;
  temp_seen = seen_map[363658].first;
  fraction_363658 = (temp_seen != 0 ? count_363658/temp_seen : 0.0);

  count_363659 = pass_map[363659].first;
  error_363659 = pass_map[363659].second;
  temp_seen = seen_map[363659].first;
  fraction_363659 = (temp_seen != 0 ? count_363659/temp_seen : 0.0);

  count_363660 = pass_map[363660].first;
  error_363660 = pass_map[363660].second;
  temp_seen = seen_map[363660].first;
  fraction_363660 = (temp_seen != 0 ? count_363660/temp_seen : 0.0);

  count_363661 = pass_map[363661].first;
  error_363661 = pass_map[363661].second;
  temp_seen = seen_map[363661].first;
  fraction_363661 = (temp_seen != 0 ? count_363661/temp_seen : 0.0);

  count_363662 = pass_map[363662].first;
  error_363662 = pass_map[363662].second;
  temp_seen = seen_map[363662].first;
  fraction_363662 = (temp_seen != 0 ? count_363662/temp_seen : 0.0);

  count_363663 = pass_map[363663].first;
  error_363663 = pass_map[363663].second;
  temp_seen = seen_map[363663].first;
  fraction_363663 = (temp_seen != 0 ? count_363663/temp_seen : 0.0);

  count_363664 = pass_map[363664].first;
  error_363664 = pass_map[363664].second;
  temp_seen = seen_map[363664].first;
  fraction_363664 = (temp_seen != 0 ? count_363664/temp_seen : 0.0);

  count_363665 = pass_map[363665].first;
  error_363665 = pass_map[363665].second;
  temp_seen = seen_map[363665].first;
  fraction_363665 = (temp_seen != 0 ? count_363665/temp_seen : 0.0);

  count_363666 = pass_map[363666].first;
  error_363666 = pass_map[363666].second;
  temp_seen = seen_map[363666].first;
  fraction_363666 = (temp_seen != 0 ? count_363666/temp_seen : 0.0);

  count_363667 = pass_map[363667].first;
  error_363667 = pass_map[363667].second;
  temp_seen = seen_map[363667].first;
  fraction_363667 = (temp_seen != 0 ? count_363667/temp_seen : 0.0);

  count_363668 = pass_map[363668].first;
  error_363668 = pass_map[363668].second;
  temp_seen = seen_map[363668].first;
  fraction_363668 = (temp_seen != 0 ? count_363668/temp_seen : 0.0);

  count_363669 = pass_map[363669].first;
  error_363669 = pass_map[363669].second;
  temp_seen = seen_map[363669].first;
  fraction_363669 = (temp_seen != 0 ? count_363669/temp_seen : 0.0);

  count_363670 = pass_map[363670].first;
  error_363670 = pass_map[363670].second;
  temp_seen = seen_map[363670].first;
  fraction_363670 = (temp_seen != 0 ? count_363670/temp_seen : 0.0);

  count_363671 = pass_map[363671].first;
  error_363671 = pass_map[363671].second;
  temp_seen = seen_map[363671].first;
  fraction_363671 = (temp_seen != 0 ? count_363671/temp_seen : 0.0);

}

void Train::SetupOutput() {
  outputFile = new TFile("ssww.root", "RECREATE");
  t_out = new TTree("RGS", "RGS output");

  t_out->Branch("mll",                    &o_mll);
  t_out->Branch("mjj",                    &o_mjj);
  t_out->Branch("lepjet_centrality",      &o_centrality);
  t_out->Branch("leptons_selected_l0_pt", &o_lep0pt);
  t_out->Branch("leptons_selected_l1_pt", &o_lep1pt);
  t_out->Branch("jets_selected_j0_pt",    &o_jet0pt);
  t_out->Branch("jets_selected_j1_pt",    &o_jet1pt);

  t_out->Branch("cutpointindex", &cp_index);

  t_out->Branch("count_999999"   , &count_999999);
  t_out->Branch("error_999999"   , &error_999999);
  t_out->Branch("fraction_999999", &fraction_999999);
  t_out->Branch("count_111111"   , &count_111111);
  t_out->Branch("error_111111"   , &error_111111);
  t_out->Branch("fraction_111111", &fraction_111111);
  t_out->Branch("count_222222"   , &count_222222);
  t_out->Branch("error_222222"   , &error_222222);
  t_out->Branch("fraction_222222", &fraction_222222);
  t_out->Branch("count_990031"   , &count_990031);
  t_out->Branch("error_990031"   , &error_990031);
  t_out->Branch("fraction_990031", &fraction_990031);
  t_out->Branch("count_123456"   , &count_123456);
  t_out->Branch("error_123456"   , &error_123456);
  t_out->Branch("fraction_123456", &fraction_123456);
  t_out->Branch("count_364284"   , &count_364284);
  t_out->Branch("error_364284"   , &error_364284);
  t_out->Branch("fraction_364284", &fraction_364284);
  t_out->Branch("count_364250"   , &count_364250);
  t_out->Branch("error_364250"   , &error_364250);
  t_out->Branch("fraction_364250", &fraction_364250);
  t_out->Branch("count_364254"   , &count_364254);
  t_out->Branch("error_364254"   , &error_364254);
  t_out->Branch("fraction_364254", &fraction_364254);
  t_out->Branch("count_364255"   , &count_364255);
  t_out->Branch("error_364255"   , &error_364255);
  t_out->Branch("fraction_364255", &fraction_364255);
  t_out->Branch("count_363718"   , &count_363718);
  t_out->Branch("error_363718"   , &error_363718);
  t_out->Branch("fraction_363718", &fraction_363718);
  t_out->Branch("count_363719"   , &count_363719);
  t_out->Branch("error_363719"   , &error_363719);
  t_out->Branch("fraction_363719", &fraction_363719);
  t_out->Branch("count_364242"   , &count_364242);
  t_out->Branch("error_364242"   , &error_364242);
  t_out->Branch("fraction_364242", &fraction_364242);
  t_out->Branch("count_364243"   , &count_364243);
  t_out->Branch("error_364243"   , &error_364243);
  t_out->Branch("fraction_364243", &fraction_364243);
  t_out->Branch("count_364244"   , &count_364244);
  t_out->Branch("error_364244"   , &error_364244);
  t_out->Branch("fraction_364244", &fraction_364244);
  t_out->Branch("count_364245"   , &count_364245);
  t_out->Branch("error_364245"   , &error_364245);
  t_out->Branch("fraction_364245", &fraction_364245);
  t_out->Branch("count_364246"   , &count_364246);
  t_out->Branch("error_364246"   , &error_364246);
  t_out->Branch("fraction_364246", &fraction_364246);
  t_out->Branch("count_364336"   , &count_364336);
  t_out->Branch("error_364336"   , &error_364336);
  t_out->Branch("fraction_364336", &fraction_364336);
  t_out->Branch("count_364337"   , &count_364337);
  t_out->Branch("error_364337"   , &error_364337);
  t_out->Branch("fraction_364337", &fraction_364337);
  t_out->Branch("count_364338"   , &count_364338);
  t_out->Branch("error_364338"   , &error_364338);
  t_out->Branch("fraction_364338", &fraction_364338);
  t_out->Branch("count_364339"   , &count_364339);
  t_out->Branch("error_364339"   , &error_364339);
  t_out->Branch("fraction_364339", &fraction_364339);
  t_out->Branch("count_363507"   , &count_363507);
  t_out->Branch("error_363507"   , &error_363507);
  t_out->Branch("fraction_363507", &fraction_363507);
  t_out->Branch("count_363508"   , &count_363508);
  t_out->Branch("error_363508"   , &error_363508);
  t_out->Branch("fraction_363508", &fraction_363508);
  t_out->Branch("count_363509"   , &count_363509);
  t_out->Branch("error_363509"   , &error_363509);
  t_out->Branch("fraction_363509", &fraction_363509);
  t_out->Branch("count_410155"   , &count_410155);
  t_out->Branch("error_410155"   , &error_410155);
  t_out->Branch("fraction_410155", &fraction_410155);
  t_out->Branch("count_410218"   , &count_410218);
  t_out->Branch("error_410218"   , &error_410218);
  t_out->Branch("fraction_410218", &fraction_410218);
  t_out->Branch("count_410219"   , &count_410219);
  t_out->Branch("error_410219"   , &error_410219);
  t_out->Branch("fraction_410219", &fraction_410219);
  t_out->Branch("count_410220"   , &count_410220);
  t_out->Branch("error_410220"   , &error_410220);
  t_out->Branch("fraction_410220", &fraction_410220);
  t_out->Branch("count_410642"   , &count_410642);
  t_out->Branch("error_410642"   , &error_410642);
  t_out->Branch("fraction_410642", &fraction_410642);
  t_out->Branch("count_410643"   , &count_410643);
  t_out->Branch("error_410643"   , &error_410643);
  t_out->Branch("fraction_410643", &fraction_410643);
  t_out->Branch("count_410644"   , &count_410644);
  t_out->Branch("error_410644"   , &error_410644);
  t_out->Branch("fraction_410644", &fraction_410644);
  t_out->Branch("count_410645"   , &count_410645);
  t_out->Branch("error_410645"   , &error_410645);
  t_out->Branch("fraction_410645", &fraction_410645);
  t_out->Branch("count_410501"   , &count_410501);
  t_out->Branch("error_410501"   , &error_410501);
  t_out->Branch("fraction_410501", &fraction_410501);
  t_out->Branch("count_147806"   , &count_147806);
  t_out->Branch("error_147806"   , &error_147806);
  t_out->Branch("fraction_147806", &fraction_147806);
  t_out->Branch("count_147807"   , &count_147807);
  t_out->Branch("error_147807"   , &error_147807);
  t_out->Branch("fraction_147807", &fraction_147807);
  t_out->Branch("count_363600"   , &count_363600);
  t_out->Branch("error_363600"   , &error_363600);
  t_out->Branch("fraction_363600", &fraction_363600);
  t_out->Branch("count_363601"   , &count_363601);
  t_out->Branch("error_363601"   , &error_363601);
  t_out->Branch("fraction_363601", &fraction_363601);
  t_out->Branch("count_363602"   , &count_363602);
  t_out->Branch("error_363602"   , &error_363602);
  t_out->Branch("fraction_363602", &fraction_363602);
  t_out->Branch("count_363603"   , &count_363603);
  t_out->Branch("error_363603"   , &error_363603);
  t_out->Branch("fraction_363603", &fraction_363603);
  t_out->Branch("count_363604"   , &count_363604);
  t_out->Branch("error_363604"   , &error_363604);
  t_out->Branch("fraction_363604", &fraction_363604);
  t_out->Branch("count_363605"   , &count_363605);
  t_out->Branch("error_363605"   , &error_363605);
  t_out->Branch("fraction_363605", &fraction_363605);
  t_out->Branch("count_363606"   , &count_363606);
  t_out->Branch("error_363606"   , &error_363606);
  t_out->Branch("fraction_363606", &fraction_363606);
  t_out->Branch("count_363607"   , &count_363607);
  t_out->Branch("error_363607"   , &error_363607);
  t_out->Branch("fraction_363607", &fraction_363607);
  t_out->Branch("count_363608"   , &count_363608);
  t_out->Branch("error_363608"   , &error_363608);
  t_out->Branch("fraction_363608", &fraction_363608);
  t_out->Branch("count_363609"   , &count_363609);
  t_out->Branch("error_363609"   , &error_363609);
  t_out->Branch("fraction_363609", &fraction_363609);
  t_out->Branch("count_363610"   , &count_363610);
  t_out->Branch("error_363610"   , &error_363610);
  t_out->Branch("fraction_363610", &fraction_363610);
  t_out->Branch("count_363611"   , &count_363611);
  t_out->Branch("error_363611"   , &error_363611);
  t_out->Branch("fraction_363611", &fraction_363611);
  t_out->Branch("count_363612"   , &count_363612);
  t_out->Branch("error_363612"   , &error_363612);
  t_out->Branch("fraction_363612", &fraction_363612);
  t_out->Branch("count_363613"   , &count_363613);
  t_out->Branch("error_363613"   , &error_363613);
  t_out->Branch("fraction_363613", &fraction_363613);
  t_out->Branch("count_363614"   , &count_363614);
  t_out->Branch("error_363614"   , &error_363614);
  t_out->Branch("fraction_363614", &fraction_363614);
  t_out->Branch("count_363615"   , &count_363615);
  t_out->Branch("error_363615"   , &error_363615);
  t_out->Branch("fraction_363615", &fraction_363615);
  t_out->Branch("count_363616"   , &count_363616);
  t_out->Branch("error_363616"   , &error_363616);
  t_out->Branch("fraction_363616", &fraction_363616);
  t_out->Branch("count_363617"   , &count_363617);
  t_out->Branch("error_363617"   , &error_363617);
  t_out->Branch("fraction_363617", &fraction_363617);
  t_out->Branch("count_363618"   , &count_363618);
  t_out->Branch("error_363618"   , &error_363618);
  t_out->Branch("fraction_363618", &fraction_363618);
  t_out->Branch("count_363619"   , &count_363619);
  t_out->Branch("error_363619"   , &error_363619);
  t_out->Branch("fraction_363619", &fraction_363619);
  t_out->Branch("count_363620"   , &count_363620);
  t_out->Branch("error_363620"   , &error_363620);
  t_out->Branch("fraction_363620", &fraction_363620);
  t_out->Branch("count_363621"   , &count_363621);
  t_out->Branch("error_363621"   , &error_363621);
  t_out->Branch("fraction_363621", &fraction_363621);
  t_out->Branch("count_363622"   , &count_363622);
  t_out->Branch("error_363622"   , &error_363622);
  t_out->Branch("fraction_363622", &fraction_363622);
  t_out->Branch("count_363623"   , &count_363623);
  t_out->Branch("error_363623"   , &error_363623);
  t_out->Branch("fraction_363623", &fraction_363623);
  t_out->Branch("count_363624"   , &count_363624);
  t_out->Branch("error_363624"   , &error_363624);
  t_out->Branch("fraction_363624", &fraction_363624);
  t_out->Branch("count_363625"   , &count_363625);
  t_out->Branch("error_363625"   , &error_363625);
  t_out->Branch("fraction_363625", &fraction_363625);
  t_out->Branch("count_363626"   , &count_363626);
  t_out->Branch("error_363626"   , &error_363626);
  t_out->Branch("fraction_363626", &fraction_363626);
  t_out->Branch("count_363627"   , &count_363627);
  t_out->Branch("error_363627"   , &error_363627);
  t_out->Branch("fraction_363627", &fraction_363627);
  t_out->Branch("count_363628"   , &count_363628);
  t_out->Branch("error_363628"   , &error_363628);
  t_out->Branch("fraction_363628", &fraction_363628);
  t_out->Branch("count_363629"   , &count_363629);
  t_out->Branch("error_363629"   , &error_363629);
  t_out->Branch("fraction_363629", &fraction_363629);
  t_out->Branch("count_363630"   , &count_363630);
  t_out->Branch("error_363630"   , &error_363630);
  t_out->Branch("fraction_363630", &fraction_363630);
  t_out->Branch("count_363631"   , &count_363631);
  t_out->Branch("error_363631"   , &error_363631);
  t_out->Branch("fraction_363631", &fraction_363631);
  t_out->Branch("count_363632"   , &count_363632);
  t_out->Branch("error_363632"   , &error_363632);
  t_out->Branch("fraction_363632", &fraction_363632);
  t_out->Branch("count_363633"   , &count_363633);
  t_out->Branch("error_363633"   , &error_363633);
  t_out->Branch("fraction_363633", &fraction_363633);
  t_out->Branch("count_363634"   , &count_363634);
  t_out->Branch("error_363634"   , &error_363634);
  t_out->Branch("fraction_363634", &fraction_363634);
  t_out->Branch("count_363635"   , &count_363635);
  t_out->Branch("error_363635"   , &error_363635);
  t_out->Branch("fraction_363635", &fraction_363635);
  t_out->Branch("count_363636"   , &count_363636);
  t_out->Branch("error_363636"   , &error_363636);
  t_out->Branch("fraction_363636", &fraction_363636);
  t_out->Branch("count_363637"   , &count_363637);
  t_out->Branch("error_363637"   , &error_363637);
  t_out->Branch("fraction_363637", &fraction_363637);
  t_out->Branch("count_363638"   , &count_363638);
  t_out->Branch("error_363638"   , &error_363638);
  t_out->Branch("fraction_363638", &fraction_363638);
  t_out->Branch("count_363639"   , &count_363639);
  t_out->Branch("error_363639"   , &error_363639);
  t_out->Branch("fraction_363639", &fraction_363639);
  t_out->Branch("count_363640"   , &count_363640);
  t_out->Branch("error_363640"   , &error_363640);
  t_out->Branch("fraction_363640", &fraction_363640);
  t_out->Branch("count_363641"   , &count_363641);
  t_out->Branch("error_363641"   , &error_363641);
  t_out->Branch("fraction_363641", &fraction_363641);
  t_out->Branch("count_363642"   , &count_363642);
  t_out->Branch("error_363642"   , &error_363642);
  t_out->Branch("fraction_363642", &fraction_363642);
  t_out->Branch("count_363643"   , &count_363643);
  t_out->Branch("error_363643"   , &error_363643);
  t_out->Branch("fraction_363643", &fraction_363643);
  t_out->Branch("count_363644"   , &count_363644);
  t_out->Branch("error_363644"   , &error_363644);
  t_out->Branch("fraction_363644", &fraction_363644);
  t_out->Branch("count_363645"   , &count_363645);
  t_out->Branch("error_363645"   , &error_363645);
  t_out->Branch("fraction_363645", &fraction_363645);
  t_out->Branch("count_363646"   , &count_363646);
  t_out->Branch("error_363646"   , &error_363646);
  t_out->Branch("fraction_363646", &fraction_363646);
  t_out->Branch("count_363647"   , &count_363647);
  t_out->Branch("error_363647"   , &error_363647);
  t_out->Branch("fraction_363647", &fraction_363647);
  t_out->Branch("count_363648"   , &count_363648);
  t_out->Branch("error_363648"   , &error_363648);
  t_out->Branch("fraction_363648", &fraction_363648);
  t_out->Branch("count_363649"   , &count_363649);
  t_out->Branch("error_363649"   , &error_363649);
  t_out->Branch("fraction_363649", &fraction_363649);
  t_out->Branch("count_363650"   , &count_363650);
  t_out->Branch("error_363650"   , &error_363650);
  t_out->Branch("fraction_363650", &fraction_363650);
  t_out->Branch("count_363651"   , &count_363651);
  t_out->Branch("error_363651"   , &error_363651);
  t_out->Branch("fraction_363651", &fraction_363651);
  t_out->Branch("count_363652"   , &count_363652);
  t_out->Branch("error_363652"   , &error_363652);
  t_out->Branch("fraction_363652", &fraction_363652);
  t_out->Branch("count_363653"   , &count_363653);
  t_out->Branch("error_363653"   , &error_363653);
  t_out->Branch("fraction_363653", &fraction_363653);
  t_out->Branch("count_363654"   , &count_363654);
  t_out->Branch("error_363654"   , &error_363654);
  t_out->Branch("fraction_363654", &fraction_363654);
  t_out->Branch("count_363655"   , &count_363655);
  t_out->Branch("error_363655"   , &error_363655);
  t_out->Branch("fraction_363655", &fraction_363655);
  t_out->Branch("count_363656"   , &count_363656);
  t_out->Branch("error_363656"   , &error_363656);
  t_out->Branch("fraction_363656", &fraction_363656);
  t_out->Branch("count_363657"   , &count_363657);
  t_out->Branch("error_363657"   , &error_363657);
  t_out->Branch("fraction_363657", &fraction_363657);
  t_out->Branch("count_363658"   , &count_363658);
  t_out->Branch("error_363658"   , &error_363658);
  t_out->Branch("fraction_363658", &fraction_363658);
  t_out->Branch("count_363659"   , &count_363659);
  t_out->Branch("error_363659"   , &error_363659);
  t_out->Branch("fraction_363659", &fraction_363659);
  t_out->Branch("count_363660"   , &count_363660);
  t_out->Branch("error_363660"   , &error_363660);
  t_out->Branch("fraction_363660", &fraction_363660);
  t_out->Branch("count_363661"   , &count_363661);
  t_out->Branch("error_363661"   , &error_363661);
  t_out->Branch("fraction_363661", &fraction_363661);
  t_out->Branch("count_363662"   , &count_363662);
  t_out->Branch("error_363662"   , &error_363662);
  t_out->Branch("fraction_363662", &fraction_363662);
  t_out->Branch("count_363663"   , &count_363663);
  t_out->Branch("error_363663"   , &error_363663);
  t_out->Branch("fraction_363663", &fraction_363663);
  t_out->Branch("count_363664"   , &count_363664);
  t_out->Branch("error_363664"   , &error_363664);
  t_out->Branch("fraction_363664", &fraction_363664);
  t_out->Branch("count_363665"   , &count_363665);
  t_out->Branch("error_363665"   , &error_363665);
  t_out->Branch("fraction_363665", &fraction_363665);
  t_out->Branch("count_363666"   , &count_363666);
  t_out->Branch("error_363666"   , &error_363666);
  t_out->Branch("fraction_363666", &fraction_363666);
  t_out->Branch("count_363667"   , &count_363667);
  t_out->Branch("error_363667"   , &error_363667);
  t_out->Branch("fraction_363667", &fraction_363667);
  t_out->Branch("count_363668"   , &count_363668);
  t_out->Branch("error_363668"   , &error_363668);
  t_out->Branch("fraction_363668", &fraction_363668);
  t_out->Branch("count_363669"   , &count_363669);
  t_out->Branch("error_363669"   , &error_363669);
  t_out->Branch("fraction_363669", &fraction_363669);
  t_out->Branch("count_363670"   , &count_363670);
  t_out->Branch("error_363670"   , &error_363670);
  t_out->Branch("fraction_363670", &fraction_363670);
  t_out->Branch("count_363671"   , &count_363671);
  t_out->Branch("error_363671"   , &error_363671);
  t_out->Branch("fraction_363671", &fraction_363671);

  t_total = new TH1F("total", "total", 120,0,120);

}

void Train::FillTotals(std::map<int, std::pair<double, double> > totals) {
  int bin = 1;

  if(totals.count(999999)) {
    t_total->SetBinContent(bin, totals[999999].first);
    t_total->SetBinError  (bin, sqrt(totals[999999].second));
  }
  bin++;

  if(totals.count(111111)) {
    t_total->SetBinContent(bin, totals[111111].first);
    t_total->SetBinError  (bin, sqrt(totals[111111].second));
  }
  bin++;

  if(totals.count(222222)) {
    t_total->SetBinContent(bin, totals[222222].first);
    t_total->SetBinError  (bin, sqrt(totals[222222].second));
  }
  bin++;

  if(totals.count(990031)) {
    t_total->SetBinContent(bin, totals[990031].first);
    t_total->SetBinError  (bin, sqrt(totals[990031].second));
  }
  bin++;

  if(totals.count(123456)) {
    t_total->SetBinContent(bin, totals[123456].first);
    t_total->SetBinError  (bin, sqrt(totals[123456].second));
  }
  bin++;

  if(totals.count(364284)) {
    t_total->SetBinContent(bin, totals[364284].first);
    t_total->SetBinError  (bin, sqrt(totals[364284].second));
  }
  bin++;

  if(totals.count(364250)) {
    t_total->SetBinContent(bin, totals[364250].first);
    t_total->SetBinError  (bin, sqrt(totals[364250].second));
  }
  bin++;

  if(totals.count(364254)) {
    t_total->SetBinContent(bin, totals[364254].first);
    t_total->SetBinError  (bin, sqrt(totals[364254].second));
  }
  bin++;

  if(totals.count(364255)) {
    t_total->SetBinContent(bin, totals[364255].first);
    t_total->SetBinError  (bin, sqrt(totals[364255].second));
  }
  bin++;

  if(totals.count(363718)) {
    t_total->SetBinContent(bin, totals[363718].first);
    t_total->SetBinError  (bin, sqrt(totals[363718].second));
  }
  bin++;

  if(totals.count(363719)) {
    t_total->SetBinContent(bin, totals[363719].first);
    t_total->SetBinError  (bin, sqrt(totals[363719].second));
  }
  bin++;

  if(totals.count(364242)) {
    t_total->SetBinContent(bin, totals[364242].first);
    t_total->SetBinError  (bin, sqrt(totals[364242].second));
  }
  bin++;

  if(totals.count(364243)) {
    t_total->SetBinContent(bin, totals[364243].first);
    t_total->SetBinError  (bin, sqrt(totals[364243].second));
  }
  bin++;

  if(totals.count(364244)) {
    t_total->SetBinContent(bin, totals[364244].first);
    t_total->SetBinError  (bin, sqrt(totals[364244].second));
  }
  bin++;

  if(totals.count(364245)) {
    t_total->SetBinContent(bin, totals[364245].first);
    t_total->SetBinError  (bin, sqrt(totals[364245].second));
  }
  bin++;

  if(totals.count(364246)) {
    t_total->SetBinContent(bin, totals[364246].first);
    t_total->SetBinError  (bin, sqrt(totals[364246].second));
  }
  bin++;

  if(totals.count(364336)) {
    t_total->SetBinContent(bin, totals[364336].first);
    t_total->SetBinError  (bin, sqrt(totals[364336].second));
  }
  bin++;

  if(totals.count(364337)) {
    t_total->SetBinContent(bin, totals[364337].first);
    t_total->SetBinError  (bin, sqrt(totals[364337].second));
  }
  bin++;

  if(totals.count(364338)) {
    t_total->SetBinContent(bin, totals[364338].first);
    t_total->SetBinError  (bin, sqrt(totals[364338].second));
  }
  bin++;

  if(totals.count(364339)) {
    t_total->SetBinContent(bin, totals[364339].first);
    t_total->SetBinError  (bin, sqrt(totals[364339].second));
  }
  bin++;

  if(totals.count(363507)) {
    t_total->SetBinContent(bin, totals[363507].first);
    t_total->SetBinError  (bin, sqrt(totals[363507].second));
  }
  bin++;

  if(totals.count(363508)) {
    t_total->SetBinContent(bin, totals[363508].first);
    t_total->SetBinError  (bin, sqrt(totals[363508].second));
  }
  bin++;

  if(totals.count(363509)) {
    t_total->SetBinContent(bin, totals[363509].first);
    t_total->SetBinError  (bin, sqrt(totals[363509].second));
  }
  bin++;

  if(totals.count(410155)) {
    t_total->SetBinContent(bin, totals[410155].first);
    t_total->SetBinError  (bin, sqrt(totals[410155].second));
  }
  bin++;

  if(totals.count(410218)) {
    t_total->SetBinContent(bin, totals[410218].first);
    t_total->SetBinError  (bin, sqrt(totals[410218].second));
  }
  bin++;

  if(totals.count(410219)) {
    t_total->SetBinContent(bin, totals[410219].first);
    t_total->SetBinError  (bin, sqrt(totals[410219].second));
  }
  bin++;

  if(totals.count(410220)) {
    t_total->SetBinContent(bin, totals[410220].first);
    t_total->SetBinError  (bin, sqrt(totals[410220].second));
  }
  bin++;

  if(totals.count(410642)) {
    t_total->SetBinContent(bin, totals[410642].first);
    t_total->SetBinError  (bin, sqrt(totals[410642].second));
  }
  bin++;

  if(totals.count(410643)) {
    t_total->SetBinContent(bin, totals[410643].first);
    t_total->SetBinError  (bin, sqrt(totals[410643].second));
  }
  bin++;

  if(totals.count(410644)) {
    t_total->SetBinContent(bin, totals[410644].first);
    t_total->SetBinError  (bin, sqrt(totals[410644].second));
  }
  bin++;

  if(totals.count(410645)) {
    t_total->SetBinContent(bin, totals[410645].first);
    t_total->SetBinError  (bin, sqrt(totals[410645].second));
  }
  bin++;

  if(totals.count(410501)) {
    t_total->SetBinContent(bin, totals[410501].first);
    t_total->SetBinError  (bin, sqrt(totals[410501].second));
  }
  bin++;

  if(totals.count(147806)) {
    t_total->SetBinContent(bin, totals[147806].first);
    t_total->SetBinError  (bin, sqrt(totals[147806].second));
  }
  bin++;

  if(totals.count(147807)) {
    t_total->SetBinContent(bin, totals[147807].first);
    t_total->SetBinError  (bin, sqrt(totals[147807].second));
  }
  bin++;

  if(totals.count(363600)) {
    t_total->SetBinContent(bin, totals[363600].first);
    t_total->SetBinError  (bin, sqrt(totals[363600].second));
  }
  bin++;

  if(totals.count(363601)) {
    t_total->SetBinContent(bin, totals[363601].first);
    t_total->SetBinError  (bin, sqrt(totals[363601].second));
  }
  bin++;

  if(totals.count(363602)) {
    t_total->SetBinContent(bin, totals[363602].first);
    t_total->SetBinError  (bin, sqrt(totals[363602].second));
  }
  bin++;

  if(totals.count(363603)) {
    t_total->SetBinContent(bin, totals[363603].first);
    t_total->SetBinError  (bin, sqrt(totals[363603].second));
  }
  bin++;

  if(totals.count(363604)) {
    t_total->SetBinContent(bin, totals[363604].first);
    t_total->SetBinError  (bin, sqrt(totals[363604].second));
  }
  bin++;

  if(totals.count(363605)) {
    t_total->SetBinContent(bin, totals[363605].first);
    t_total->SetBinError  (bin, sqrt(totals[363605].second));
  }
  bin++;

  if(totals.count(363606)) {
    t_total->SetBinContent(bin, totals[363606].first);
    t_total->SetBinError  (bin, sqrt(totals[363606].second));
  }
  bin++;

  if(totals.count(363607)) {
    t_total->SetBinContent(bin, totals[363607].first);
    t_total->SetBinError  (bin, sqrt(totals[363607].second));
  }
  bin++;

  if(totals.count(363608)) {
    t_total->SetBinContent(bin, totals[363608].first);
    t_total->SetBinError  (bin, sqrt(totals[363608].second));
  }
  bin++;

  if(totals.count(363609)) {
    t_total->SetBinContent(bin, totals[363609].first);
    t_total->SetBinError  (bin, sqrt(totals[363609].second));
  }
  bin++;

  if(totals.count(363610)) {
    t_total->SetBinContent(bin, totals[363610].first);
    t_total->SetBinError  (bin, sqrt(totals[363610].second));
  }
  bin++;

  if(totals.count(363611)) {
    t_total->SetBinContent(bin, totals[363611].first);
    t_total->SetBinError  (bin, sqrt(totals[363611].second));
  }
  bin++;

  if(totals.count(363612)) {
    t_total->SetBinContent(bin, totals[363612].first);
    t_total->SetBinError  (bin, sqrt(totals[363612].second));
  }
  bin++;

  if(totals.count(363613)) {
    t_total->SetBinContent(bin, totals[363613].first);
    t_total->SetBinError  (bin, sqrt(totals[363613].second));
  }
  bin++;

  if(totals.count(363614)) {
    t_total->SetBinContent(bin, totals[363614].first);
    t_total->SetBinError  (bin, sqrt(totals[363614].second));
  }
  bin++;

  if(totals.count(363615)) {
    t_total->SetBinContent(bin, totals[363615].first);
    t_total->SetBinError  (bin, sqrt(totals[363615].second));
  }
  bin++;

  if(totals.count(363616)) {
    t_total->SetBinContent(bin, totals[363616].first);
    t_total->SetBinError  (bin, sqrt(totals[363616].second));
  }
  bin++;

  if(totals.count(363617)) {
    t_total->SetBinContent(bin, totals[363617].first);
    t_total->SetBinError  (bin, sqrt(totals[363617].second));
  }
  bin++;

  if(totals.count(363618)) {
    t_total->SetBinContent(bin, totals[363618].first);
    t_total->SetBinError  (bin, sqrt(totals[363618].second));
  }
  bin++;

  if(totals.count(363619)) {
    t_total->SetBinContent(bin, totals[363619].first);
    t_total->SetBinError  (bin, sqrt(totals[363619].second));
  }
  bin++;

  if(totals.count(363620)) {
    t_total->SetBinContent(bin, totals[363620].first);
    t_total->SetBinError  (bin, sqrt(totals[363620].second));
  }
  bin++;

  if(totals.count(363621)) {
    t_total->SetBinContent(bin, totals[363621].first);
    t_total->SetBinError  (bin, sqrt(totals[363621].second));
  }
  bin++;

  if(totals.count(363622)) {
    t_total->SetBinContent(bin, totals[363622].first);
    t_total->SetBinError  (bin, sqrt(totals[363622].second));
  }
  bin++;

  if(totals.count(363623)) {
    t_total->SetBinContent(bin, totals[363623].first);
    t_total->SetBinError  (bin, sqrt(totals[363623].second));
  }
  bin++;

  if(totals.count(363624)) {
    t_total->SetBinContent(bin, totals[363624].first);
    t_total->SetBinError  (bin, sqrt(totals[363624].second));
  }
  bin++;

  if(totals.count(363625)) {
    t_total->SetBinContent(bin, totals[363625].first);
    t_total->SetBinError  (bin, sqrt(totals[363625].second));
  }
  bin++;

  if(totals.count(363626)) {
    t_total->SetBinContent(bin, totals[363626].first);
    t_total->SetBinError  (bin, sqrt(totals[363626].second));
  }
  bin++;

  if(totals.count(363627)) {
    t_total->SetBinContent(bin, totals[363627].first);
    t_total->SetBinError  (bin, sqrt(totals[363627].second));
  }
  bin++;

  if(totals.count(363628)) {
    t_total->SetBinContent(bin, totals[363628].first);
    t_total->SetBinError  (bin, sqrt(totals[363628].second));
  }
  bin++;

  if(totals.count(363629)) {
    t_total->SetBinContent(bin, totals[363629].first);
    t_total->SetBinError  (bin, sqrt(totals[363629].second));
  }
  bin++;

  if(totals.count(363630)) {
    t_total->SetBinContent(bin, totals[363630].first);
    t_total->SetBinError  (bin, sqrt(totals[363630].second));
  }
  bin++;

  if(totals.count(363631)) {
    t_total->SetBinContent(bin, totals[363631].first);
    t_total->SetBinError  (bin, sqrt(totals[363631].second));
  }
  bin++;

  if(totals.count(363632)) {
    t_total->SetBinContent(bin, totals[363632].first);
    t_total->SetBinError  (bin, sqrt(totals[363632].second));
  }
  bin++;

  if(totals.count(363633)) {
    t_total->SetBinContent(bin, totals[363633].first);
    t_total->SetBinError  (bin, sqrt(totals[363633].second));
  }
  bin++;

  if(totals.count(363634)) {
    t_total->SetBinContent(bin, totals[363634].first);
    t_total->SetBinError  (bin, sqrt(totals[363634].second));
  }
  bin++;

  if(totals.count(363635)) {
    t_total->SetBinContent(bin, totals[363635].first);
    t_total->SetBinError  (bin, sqrt(totals[363635].second));
  }
  bin++;

  if(totals.count(363636)) {
    t_total->SetBinContent(bin, totals[363636].first);
    t_total->SetBinError  (bin, sqrt(totals[363636].second));
  }
  bin++;

  if(totals.count(363637)) {
    t_total->SetBinContent(bin, totals[363637].first);
    t_total->SetBinError  (bin, sqrt(totals[363637].second));
  }
  bin++;

  if(totals.count(363638)) {
    t_total->SetBinContent(bin, totals[363638].first);
    t_total->SetBinError  (bin, sqrt(totals[363638].second));
  }
  bin++;

  if(totals.count(363639)) {
    t_total->SetBinContent(bin, totals[363639].first);
    t_total->SetBinError  (bin, sqrt(totals[363639].second));
  }
  bin++;

  if(totals.count(363640)) {
    t_total->SetBinContent(bin, totals[363640].first);
    t_total->SetBinError  (bin, sqrt(totals[363640].second));
  }
  bin++;

  if(totals.count(363641)) {
    t_total->SetBinContent(bin, totals[363641].first);
    t_total->SetBinError  (bin, sqrt(totals[363641].second));
  }
  bin++;

  if(totals.count(363642)) {
    t_total->SetBinContent(bin, totals[363642].first);
    t_total->SetBinError  (bin, sqrt(totals[363642].second));
  }
  bin++;

  if(totals.count(363643)) {
    t_total->SetBinContent(bin, totals[363643].first);
    t_total->SetBinError  (bin, sqrt(totals[363643].second));
  }
  bin++;

  if(totals.count(363644)) {
    t_total->SetBinContent(bin, totals[363644].first);
    t_total->SetBinError  (bin, sqrt(totals[363644].second));
  }
  bin++;

  if(totals.count(363645)) {
    t_total->SetBinContent(bin, totals[363645].first);
    t_total->SetBinError  (bin, sqrt(totals[363645].second));
  }
  bin++;

  if(totals.count(363646)) {
    t_total->SetBinContent(bin, totals[363646].first);
    t_total->SetBinError  (bin, sqrt(totals[363646].second));
  }
  bin++;

  if(totals.count(363647)) {
    t_total->SetBinContent(bin, totals[363647].first);
    t_total->SetBinError  (bin, sqrt(totals[363647].second));
  }
  bin++;

  if(totals.count(363648)) {
    t_total->SetBinContent(bin, totals[363648].first);
    t_total->SetBinError  (bin, sqrt(totals[363648].second));
  }
  bin++;

  if(totals.count(363649)) {
    t_total->SetBinContent(bin, totals[363649].first);
    t_total->SetBinError  (bin, sqrt(totals[363649].second));
  }
  bin++;

  if(totals.count(363650)) {
    t_total->SetBinContent(bin, totals[363650].first);
    t_total->SetBinError  (bin, sqrt(totals[363650].second));
  }
  bin++;

  if(totals.count(363651)) {
    t_total->SetBinContent(bin, totals[363651].first);
    t_total->SetBinError  (bin, sqrt(totals[363651].second));
  }
  bin++;

  if(totals.count(363652)) {
    t_total->SetBinContent(bin, totals[363652].first);
    t_total->SetBinError  (bin, sqrt(totals[363652].second));
  }
  bin++;

  if(totals.count(363653)) {
    t_total->SetBinContent(bin, totals[363653].first);
    t_total->SetBinError  (bin, sqrt(totals[363653].second));
  }
  bin++;

  if(totals.count(363654)) {
    t_total->SetBinContent(bin, totals[363654].first);
    t_total->SetBinError  (bin, sqrt(totals[363654].second));
  }
  bin++;

  if(totals.count(363655)) {
    t_total->SetBinContent(bin, totals[363655].first);
    t_total->SetBinError  (bin, sqrt(totals[363655].second));
  }
  bin++;

  if(totals.count(363656)) {
    t_total->SetBinContent(bin, totals[363656].first);
    t_total->SetBinError  (bin, sqrt(totals[363656].second));
  }
  bin++;

  if(totals.count(363657)) {
    t_total->SetBinContent(bin, totals[363657].first);
    t_total->SetBinError  (bin, sqrt(totals[363657].second));
  }
  bin++;

  if(totals.count(363658)) {
    t_total->SetBinContent(bin, totals[363658].first);
    t_total->SetBinError  (bin, sqrt(totals[363658].second));
  }
  bin++;

  if(totals.count(363659)) {
    t_total->SetBinContent(bin, totals[363659].first);
    t_total->SetBinError  (bin, sqrt(totals[363659].second));
  }
  bin++;

  if(totals.count(363660)) {
    t_total->SetBinContent(bin, totals[363660].first);
    t_total->SetBinError  (bin, sqrt(totals[363660].second));
  }
  bin++;

  if(totals.count(363661)) {
    t_total->SetBinContent(bin, totals[363661].first);
    t_total->SetBinError  (bin, sqrt(totals[363661].second));
  }
  bin++;

  if(totals.count(363662)) {
    t_total->SetBinContent(bin, totals[363662].first);
    t_total->SetBinError  (bin, sqrt(totals[363662].second));
  }
  bin++;

  if(totals.count(363663)) {
    t_total->SetBinContent(bin, totals[363663].first);
    t_total->SetBinError  (bin, sqrt(totals[363663].second));
  }
  bin++;

  if(totals.count(363664)) {
    t_total->SetBinContent(bin, totals[363664].first);
    t_total->SetBinError  (bin, sqrt(totals[363664].second));
  }
  bin++;

  if(totals.count(363665)) {
    t_total->SetBinContent(bin, totals[363665].first);
    t_total->SetBinError  (bin, sqrt(totals[363665].second));
  }
  bin++;

  if(totals.count(363666)) {
    t_total->SetBinContent(bin, totals[363666].first);
    t_total->SetBinError  (bin, sqrt(totals[363666].second));
  }
  bin++;

  if(totals.count(363667)) {
    t_total->SetBinContent(bin, totals[363667].first);
    t_total->SetBinError  (bin, sqrt(totals[363667].second));
  }
  bin++;

  if(totals.count(363668)) {
    t_total->SetBinContent(bin, totals[363668].first);
    t_total->SetBinError  (bin, sqrt(totals[363668].second));
  }
  bin++;

  if(totals.count(363669)) {
    t_total->SetBinContent(bin, totals[363669].first);
    t_total->SetBinError  (bin, sqrt(totals[363669].second));
  }
  bin++;

  if(totals.count(363670)) {
    t_total->SetBinContent(bin, totals[363670].first);
    t_total->SetBinError  (bin, sqrt(totals[363670].second));
  }
  bin++;

  if(totals.count(363671)) {
    t_total->SetBinContent(bin, totals[363671].first);
    t_total->SetBinError  (bin, sqrt(totals[363671].second));
  }
  bin++;

}

void Train::FinalizeOutput() {
  t_out->Write();
  t_total->Write();
  outputFile->Close();
}
