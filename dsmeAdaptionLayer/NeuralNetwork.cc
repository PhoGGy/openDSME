/*
 * openDSME
 *
 * Implementation of the Deterministic & Synchronous Multi-channel Extension (DSME)
 * described in the IEEE 802.15.4-2015 standard
 *
 * Authors: Florian Kauer <florian.kauer@tuhh.de>
 *          Maximilian Koestler <maximilian.koestler@tuhh.de>
 *          Sandrina Backhauss <sandrina.backhauss@tuhh.de>
 *
 * Based on
 *          DSME Implementation for the INET Framework
 *          Tobias Luebkert <tobias.luebkert@tuhh.de>
 *
 * Copyright (c) 2015, Institute of Telematics, Hamburg University of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "./NeuralNetwork.h"

namespace dsme {

/******** Layer 0 ********/
static const float l0_weights_array[80] {
    -6.67625093,-1.05778015,-7.09029007,6.64986324,
    3.86944127,0.80678463,-3.21917009,8.05850983,
    7.73383904,-0.98878247,17.37286186,-1.54971385,
    6.91079712,-1.74152184,-1.82198763,-0.98793614,
    14.02704144,-16.18549919,4.97361994,-3.70149112,
    -6.35735226,-3.92711735,-3.22993827,-1.94725943,
    -5.22548389,-14.73730564,-7.00202370,-0.54954350,
    6.35768604,3.04587770,-4.53325701,1.71480072,
    2.44201779,14.80858326,0.66040081,6.38803530,
    7.72414684,3.11541367,-1.36562979,-5.53668499,
    -6.64479351,-1.34512198,-7.08218050,-1.61808014,
    -12.24700069,2.25424147,-6.77706432,0.70836824,
    6.07329464,4.13138533,17.55744171,-2.20948029,
    9.32527828,12.10322094,-4.58844185,1.14194286,
    3.70144105,1.30729425,13.85949612,-6.05625105,
    -12.10829449,-6.61061907,1.00637102,-1.02796483,
    10.89506817,-1.12153554,10.42376232,-4.27825499,
    -2.28673673,-10.67702198,-17.12964058,2.08402729,
    11.72310543,0.59173328,9.52414513,2.36938834,
    14.05286503,-3.72429872,6.61671829,-0.64187920,
};
static float l0_bias_array[20] {
    -1.20761347,-3.34157920,-1.28734112,-2.27046776,-1.15484476,2.31786084,1.40367007,-2.03877664,-2.46179438,0.88661015,0.96751106,-0.30069447,-0.95562202,-0.66830283,0.99924290,0.31789538,-0.43953818,0.15432747,-2.23532605,-1.34932911
};
static float l0_output_array[20];

static const quicknet::matrix_t l0_weights{20,4,l0_weights_array};
static const quicknet::vector_t l0_bias{20,l0_bias_array};
static quicknet::vector_t l0_output{20,l0_output_array};

/******** Layer 1 ********/
static const float l1_weights_array[400] {
    1.52454472,0.39504135,-3.68076253,-2.37311387,-2.08042741,2.29657888,1.13241673,-1.25413179,-0.64815605,-1.57317746,2.30014825,2.38897920,-3.31757402,-1.48521411,-2.63720584,2.41180086,-3.78004313,1.58692169,-3.46375346,-4.18409395,
    3.63879848,4.65169144,3.15726256,-6.15918064,0.88470215,-2.64273310,-2.37158036,-3.96177363,4.50589228,-5.01840973,-2.17316175,-0.39069259,2.97087240,0.86211753,-1.80838394,-0.45837089,-0.33290419,-1.39881027,4.08964252,1.65584934,
    2.61543775,0.73191184,-3.52230549,-3.79655361,-4.09084892,1.93425417,0.51303428,-1.60976756,1.15800226,-2.41178679,1.71841121,2.64761710,-3.61911726,-0.52097666,-3.24011612,2.37180591,-5.05363512,1.02811170,-3.86044264,-5.57029772,
    -1.83422947,-4.45808458,1.29336071,4.90295553,-1.59904826,0.83879483,-0.61594969,0.76322579,-1.84754121,-0.01712445,-0.38990211,-1.14417648,1.48850822,-2.07500839,3.20254087,1.55923009,1.08249426,-3.20091867,-0.83984929,-0.58811444,
    4.34446573,2.98471308,-3.90736842,-2.70891333,-5.93196154,1.07311392,0.17445229,1.09771776,2.00844383,-1.30432320,2.11906338,2.45080662,-3.25113177,0.42119172,-4.49486685,1.10532188,-4.26603603,2.08512783,-0.77460212,-3.23039532,
    1.50311756,3.57592249,0.09365848,-2.27071834,-0.51319307,-7.73013592,-0.19621548,-4.97055817,2.03289676,-4.17717886,-5.08092546,-2.51645160,-0.39214581,1.81516433,-3.57473302,-6.89718199,-0.81333667,3.45137906,1.92991769,1.29012334,
    1.34613943,0.67242736,-4.05693960,-1.43991232,-4.04460430,1.80887032,1.62731135,1.45148408,0.03205858,0.08681207,2.65368390,2.96837735,-4.29728460,0.07554619,-3.00535965,2.19879341,-3.98220944,3.13224840,-2.06081319,-3.10225916,
    -4.39052773,-3.10967398,0.48745561,4.40370035,4.60995579,-0.50913513,0.12997036,1.67280042,-2.03239989,4.14853859,0.02121758,-1.52217436,0.71460146,1.10727036,3.66441965,-2.81875610,2.82704282,-0.54042190,-1.01307797,1.07416344,
    -2.69915557,-3.86857796,0.24067418,1.51151669,-0.06615592,0.63641405,3.87836075,0.90882766,-3.74057698,2.82280254,-0.12799509,-0.92536193,-0.44924018,-1.27892780,3.16997194,1.73185551,1.49020505,1.20399213,-0.71685344,1.37739730,
    1.36321354,2.65878415,0.28329885,-6.38432598,3.11512733,-0.95213163,1.18305826,0.68227774,0.66394520,-1.59202933,-0.65367866,-0.76340312,-0.07035971,1.11995542,-2.86544418,-2.05100441,-0.26944596,0.88686800,1.58129954,0.92011112,
    -2.99093366,-4.08552456,-0.22736238,-0.87266666,-0.56285942,0.11417632,-0.85319829,0.39579338,-1.19818068,2.81708789,0.82337517,0.65470356,0.89780831,-0.22693789,3.77762842,0.23868607,0.60527712,-2.02164459,-1.38547873,-0.92318571,
    -5.35554981,-1.43357897,-0.40487358,3.59686470,1.82916760,-0.93514097,-0.52855307,3.16573763,-3.54917097,3.08859611,-0.55451971,-0.90219623,-0.11382180,-1.02710617,3.00678706,-1.12025142,1.88382435,-0.23893233,-1.58733809,0.69689876,
    -2.21526933,0.73298568,0.77055031,2.42049170,4.52662468,-2.67898202,-1.76244807,0.94850796,1.19469416,0.99188846,-2.02611923,-3.17325711,0.25000253,2.18049216,0.02142217,-3.80086136,2.67046022,-0.02748609,2.04844427,3.66991019,
    -2.12664151,-1.26111126,-1.72655988,5.12331295,-1.88214111,-0.14007346,-4.10056257,5.01898956,1.06657135,1.76069295,1.02653611,2.42202520,-0.50553554,-0.14713269,2.46112537,-1.12483966,-0.62849396,-2.48469067,-1.97124624,-2.46957898,
    -1.34261918,0.88376564,-0.29502901,2.01857758,-8.52493191,0.63930774,-5.24943066,5.39442444,2.40381122,2.01782274,0.80431181,1.54793966,0.94393742,2.19503736,2.49669647,-1.95476389,-0.62353247,-4.64766645,-1.08023584,-2.91826606,
    1.36340714,-0.35522649,-1.66656768,0.55434424,-4.33867598,2.20857716,2.44721961,-0.57601196,-0.48085958,0.13302922,1.54278994,-0.47627744,-2.51952934,0.17256698,-2.48731899,1.94424367,-0.75156021,4.29967070,-0.78293210,-0.28801242,
    1.32244563,-2.03596711,-0.42103386,-3.25319552,-0.10629427,2.88307357,4.37192726,-2.56099653,-5.03409195,-2.41397762,1.15390825,-0.03450059,-1.02238321,-4.73494053,-1.31554091,4.16940498,-1.38028550,1.82246780,-1.49258685,-1.61117482,
    2.92329693,0.66690803,0.85932159,-4.65607214,0.42164794,-4.53880835,-3.22913694,-7.97661877,3.45075846,-1.49085045,-1.77822208,0.75878304,1.08581257,2.09901857,-1.96069968,-3.47518849,-0.21533993,-0.32134110,1.75272775,0.58405977,
    0.07034149,-0.97348201,-3.23524022,-0.16892938,0.51339447,2.28531003,3.63330960,-0.28906110,-3.54687476,0.99942362,1.56058729,0.44915211,-3.29296184,-0.83820707,-2.01786804,1.69302285,-1.61620522,3.32530999,-2.78378201,-0.82833010,
    -0.64906734,3.09757209,1.31558907,-1.16013551,1.95073068,-11.59845543,-5.38210154,-1.89773929,1.14576650,-4.46488810,-8.10430813,-1.00873852,1.51111162,0.76824784,0.62430608,-7.28386545,0.21169829,-5.21835184,1.36814976,0.11553447,
};
static float l1_bias_array[20] {
    -0.05665173,0.28442177,-0.09908836,-0.43055779,0.96854651,-0.29608837,0.36775562,-0.56362516,-0.29673868,0.25230366,-0.23077269,-1.03517962,-0.72823298,-0.38266215,-0.02508250,0.51799798,-0.16895804,0.80923986,0.06624002,-0.81584013
};
static float l1_output_array[20];

static const quicknet::matrix_t l1_weights{20,20,l1_weights_array};
static const quicknet::vector_t l1_bias{20,l1_bias_array};
static quicknet::vector_t l1_output{20,l1_output_array};

/******** Layer 2 ********/
static const float l2_weights_array[400] {
    5.68436146,5.31825733,5.35074091,-10.47782612,-3.12105322,4.12524223,-2.01622534,-2.65548611,-3.11893201,3.69747138,-6.51911592,-1.21412718,4.43355560,-3.73490882,-1.08318996,2.14291143,-4.37954521,-3.05703306,0.18361235,0.57192165,
    -4.81475925,2.18494225,-2.67745614,-2.74906063,2.22000766,-3.92869163,1.52742803,-0.91475415,-2.24906135,0.27804399,-0.88912284,1.98414564,2.20140433,-2.66690731,-4.00501013,-0.80383861,4.09517908,-1.09823942,-4.14353800,-26.08082962,
    4.52994871,-0.58443731,5.97241402,-2.54559898,7.84094667,-5.06253242,3.96325588,-4.67484903,-1.89644885,1.01705396,-2.11380339,-2.66670036,-2.85566163,-1.00458598,0.22839844,4.26215553,-1.52855766,3.15514159,2.53285384,-8.96485996,
    3.64871812,3.28594804,5.17468119,2.75849867,1.87722754,1.45392323,0.77116102,-2.17213178,-1.62019420,-3.26954985,-0.67797738,-0.32688674,-5.14555120,1.40320551,-1.43912625,-0.09219892,2.08527851,1.87013805,0.43649343,4.58721876,
    -8.57279968,2.62023139,-2.87350035,-11.59323597,0.46288064,18.40235901,-1.22932899,-7.54801273,-8.73954964,2.11896563,-8.38669968,-13.22662926,1.43388557,-5.08446121,-2.43371844,2.82404613,2.55643582,4.36096430,-3.19255471,6.62532282,
    -5.62100363,3.05813575,-0.64404398,4.81329393,1.30296302,6.44609880,-0.98374158,-1.90260005,-2.92061758,0.24392658,-0.26494345,-4.26584291,-0.24899410,2.66431499,-1.22276354,0.32082471,-13.71595097,-4.31782532,-2.59370232,1.12503767,
    0.07254905,1.57369864,1.81233478,2.68009806,-1.32061601,-3.56132913,0.83780736,2.91160631,-0.90400600,-0.97674692,2.44026804,3.78792238,0.43523002,1.44356358,4.71397781,-1.63294780,-1.52674735,3.99078870,-2.35543776,13.90140724,
    1.80703437,-1.72791123,3.20127606,-3.71378613,1.09818673,5.49549913,1.36986530,-3.95088530,-2.12445021,-0.53488111,-4.11161661,-6.25093603,-2.05295062,-3.86019516,-5.58248854,0.03958101,-1.86318552,2.68406296,1.10954928,9.97394085,
    -4.10216904,-2.98075151,-5.48955059,2.43906450,-2.10080767,6.67345142,-6.01172543,-0.19804306,0.12944652,-2.59093833,1.89512050,1.84866297,-1.17152512,-0.33880380,-0.66636676,-5.01236153,4.35384321,5.20083380,-7.07994604,0.60263479,
    0.15157260,-6.02235222,0.38758442,3.64392018,-3.38672829,-12.62089825,-2.25739312,3.70687962,2.79674101,-1.35185421,2.34111786,3.39989448,-1.02650130,1.97353804,1.16317368,-1.40688312,-1.69275630,-0.12759201,-1.34550440,-2.26893783,
    9.30216503,-1.90800226,6.52445936,2.18871737,4.69042397,-5.68167305,13.69708920,-1.80380881,1.52429891,-2.28441238,1.44229019,-2.49619985,-1.41449332,5.80537796,5.58859444,3.83848119,15.95045853,-5.52614880,16.52993011,4.52166224,
    -13.67873478,-0.53874207,-23.48042297,-5.42201519,-1.47542548,4.14478111,-13.62861443,0.19636273,-0.14365539,0.06055740,0.73708218,-1.84811234,-1.24505985,-0.49438015,-0.36969164,-4.94445133,-3.44783711,1.41624677,-2.94963145,4.46347952,
    1.39903140,-1.94880557,3.09652972,-3.34802270,1.02478576,-4.30324793,0.66134769,-1.54666317,-0.05959601,1.53318107,-0.49714878,-5.13162422,-2.03895783,-1.60217190,0.67894071,0.15037026,0.26014969,0.88159019,-1.81522584,-6.49448729,
    1.80295086,-1.49573648,6.31949472,3.04694676,4.17583466,-9.39791965,3.85726094,-2.44566536,-1.61840594,-2.02247930,0.23856051,-0.35394165,-0.86267042,7.88027954,4.13711023,3.39357305,-2.86779189,-3.49613667,1.42808747,-4.95188284,
    -0.51910633,-0.53758794,2.32556939,2.42385364,0.03016892,4.63837910,-0.28159347,-1.81475747,0.23483607,-0.91721839,-0.87564254,-0.60816723,-0.91304475,3.49050665,-0.11701738,1.86007845,0.90835887,-1.86043334,-2.97231340,4.88595390,
    -3.94206429,-2.10504770,-6.20716000,3.04629254,0.87622494,-0.26850101,-4.25375128,1.71228433,2.49277163,0.06361065,0.84012836,3.68370175,2.37975597,-0.49986383,1.65500498,0.56652927,-5.04934263,-6.38464928,-4.54206419,-16.83617401,
    -3.87065411,0.67003542,-3.23462510,2.15298223,1.03714359,-4.28198719,-3.21345472,1.65762115,2.62065554,0.29255173,1.48105395,2.01429820,0.68072516,0.11993577,-1.26705980,-0.64246148,-9.79477596,-2.65835643,-3.69425106,-4.67365122,
    -0.53615254,1.13165724,-1.54483294,2.26407599,1.03864133,-10.37917137,-1.12056279,-1.18073738,0.31229714,-1.61209381,-0.53454047,-0.39631560,0.03140346,3.44295955,2.95564938,0.46041521,-3.86445355,-10.96009064,-1.40211535,2.58967328,
    -1.88740730,3.30159640,-1.18216228,-1.04764879,4.03307104,-3.05797696,0.40589562,0.85449004,-1.02811062,-1.14478791,-0.73662621,-1.15794623,-0.94847280,4.88312101,5.11259270,-2.54143167,-1.33599901,-3.68213630,-1.45990813,1.53442907,
    -2.81563878,-0.10551897,-1.43527782,13.76937580,0.65652949,-5.32457066,-0.52499771,-0.69202793,6.83542633,-0.35821930,15.41272068,19.73196602,-0.04673655,9.45727634,7.08582878,0.96298581,-3.23193693,-3.95555067,0.74426281,-4.33272123,
};
static float l2_bias_array[20] {
    0.53845227,-0.19120210,-0.25218999,-1.74756169,0.88528067,0.74178427,-0.40839291,-1.59780431,-0.57475096,0.18888634,-0.56692475,-1.35347307,0.68464333,-0.86929083,-0.27127555,0.52197319,1.14622676,-0.34280315,-1.39923143,0.34709850
};
static float l2_output_array[20];

static const quicknet::matrix_t l2_weights{20,20,l2_weights_array};
static const quicknet::vector_t l2_bias{20,l2_bias_array};
static quicknet::vector_t l2_output{20,l2_output_array};

/******** Layer 3 ********/
static const float l3_weights_array[300] {
    -2.12680435,-2.06525540,-2.10118055,-1.27671111,-1.77221763,-2.06819224,-2.18690062,-0.98514414,-1.89623785,-2.06208181,-2.78973699,-1.44647169,-1.18635046,-1.93671000,-1.78952587,-1.39085960,-1.58306146,-0.75539249,-1.43356681,-2.85719419,
    -0.98335850,2.16634774,-1.69944489,4.00140858,4.07696056,1.87182510,-6.83933210,6.15958357,-13.52464581,-3.14360380,-0.96540082,-13.83317089,0.86667806,-3.81311202,1.68456757,1.52758729,-1.66362441,6.17666340,-1.74734426,0.60148466,
    1.44283521,-2.16912413,2.71123338,0.27875355,2.46018887,-1.95126593,1.22029984,4.57082129,-2.02418756,-2.10048771,-1.20258045,0.06216910,1.33209205,0.58925450,-1.06055462,0.67968231,-2.07152867,2.00986767,-3.53535533,-2.01702857,
    2.48323679,-1.96772289,1.46813774,-0.02963894,2.43475509,-2.71369028,-1.24823153,-2.26908708,4.74909449,-2.33970785,0.62091601,-1.61147916,-1.38519263,0.01611350,3.10343075,6.54092884,-7.32787323,2.75525832,-1.30501187,1.24281001,
    0.54708755,0.38469744,0.76933771,-0.48783603,-1.79857767,-0.20902200,0.10577714,-1.80593181,1.77923369,-0.47434238,1.19624901,0.11392195,-0.37016901,0.12012209,3.50239301,2.70441580,-2.08426285,-1.77513349,0.85582286,-1.35684943,
    0.20942277,-0.53439152,0.36733991,0.68151957,-1.58009064,0.98740357,1.48108053,4.53179121,-1.16278315,-0.27742040,0.76462710,-3.95841146,-0.81115586,-1.75561094,-0.87859571,-1.72954071,0.66098785,1.91894019,-0.06875538,0.80271626,
    2.00912976,-3.60593486,-0.83579397,-5.63429213,-3.23999715,4.22790909,0.41204113,-4.53626585,-0.98193157,1.25654340,-1.85218298,-0.84187859,3.29066849,0.52362812,0.25713211,-1.89871860,1.47822464,1.09604919,-1.84645748,0.46120924,
    -1.74604523,1.15219903,-0.60721380,0.84002542,-1.25702977,0.76027274,-0.15672594,-17.21777725,-0.00773683,0.92680216,-0.33415872,3.34915328,-0.19293128,0.52341396,-2.67227840,-0.04509862,0.40102816,-1.61479652,2.31339741,0.69262606,
    -3.66554999,2.60635567,-2.40258050,-2.70021749,-2.46289277,1.03288329,1.58159006,-13.66759968,-1.05317235,-0.74108386,0.02213564,4.41518354,-4.14821863,0.16610533,-3.54504108,-1.36112154,1.79842734,-2.39359498,1.89080083,0.27016866,
    -0.78901201,1.84129977,-1.20145416,1.61030078,-0.34934705,-3.30571914,-2.96814299,-8.30037117,-0.34475917,0.61565429,-2.00914168,2.11894560,-23.93548584,3.98976088,-0.37547755,0.01690172,3.30967045,-2.18258190,2.18002200,-0.38419110,
    -0.56421995,-0.99367654,-7.87459803,-28.23638535,-5.03330326,-14.62224960,-1.16628587,-3.51401210,-2.10735798,0.17200856,-2.91071749,1.48393059,11.41920662,3.00081015,0.18329433,0.00697138,0.06451312,-4.34635496,0.00434428,1.46972215,
    -0.25193635,3.74408007,-6.49921179,-36.01708984,-33.75744629,-8.03233624,0.53010213,-3.14257741,-8.19184971,-0.29307789,-2.59550261,-7.99485493,-6.35023880,1.40478146,-2.65184450,0.30687591,-1.23693216,-8.65252972,-10.67125225,0.58612007,
    -6.42916632,-2.90468669,-7.96199703,-13.24105358,-11.77305317,-0.45664778,0.34895256,-2.71848226,0.14534663,-2.76050448,-6.56427574,4.66501474,-5.68683910,-8.42869473,1.28072453,-13.69277668,-4.92552948,-21.23154259,3.40617871,0.74559540,
    -4.95709515,1.74165869,-0.78707093,1.08749712,5.02929497,-2.83119249,0.02329315,-2.04610705,-8.17617798,1.40038455,1.60379398,-1.90219831,0.76300192,-0.14934447,-2.97376871,-1.42446673,1.33059990,0.36864921,1.13184667,-0.47734427,
    -1.90696406,-1.50820994,-1.65006912,-1.84191668,-1.79778504,-1.98877048,-2.62027359,-0.86967003,-1.91824162,-1.86535788,-2.79631186,-1.87459803,-1.26398528,-2.12241626,-1.86438322,-0.80226338,-1.83534086,-1.13463175,-1.21881437,-3.06788206,
};
static float l3_bias_array[15] {
    -2.79964590,-0.77756304,0.30130199,-0.87218201,0.55447459,0.31985274,0.80922383,-0.01670245,-0.18805113,-0.93196064,1.16359568,0.30011705,0.56436962,-0.97118592,-2.83411622
};
static float l3_output_array[15];

static const quicknet::matrix_t l3_weights{15,20,l3_weights_array};
static const quicknet::vector_t l3_bias{15,l3_bias_array};
static quicknet::vector_t l3_output{15,l3_output_array};

/******** Network ********/
static quicknet::Layer layers[4] {
    {l0_weights, l0_bias, l0_output, quicknet::quick_sigmoid},
    {l1_weights, l1_bias, l1_output, quicknet::quick_sigmoid},
    {l2_weights, l2_bias, l2_output, quicknet::quick_sigmoid},
    {l3_weights, l3_bias, l3_output, quicknet::quick_softmax},
};

NeuralNetwork::NeuralNetwork() : network{4, layers} {
}

} /* namespace dsme */
