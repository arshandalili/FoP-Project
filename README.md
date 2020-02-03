# FoP-Project

## register
### client
In tabeh user va pass az karbar migirad va barayeh server mifrestad va server beineh user database check mikonad agar vojood dasht error midahad agar na register mikonad va pas az register movafaq beh safheyeh asli barm migardad.
### server
In tabeh user va pass ra migirad va check mikonad agar moshkel dast error bar migardanad agar na
fileh karbar ra misazad.

## login
### client
In tabeh user va pass az karbar migirad va barayeh server mifrestad va server dar beineh user database check mikonad agar vojood nadasht error midahad agar dasht check mikonad keh password dorost ast agar Ok bood yek authtoken tolid mikonad va login dar client in ra dar yek global array save mikonad.
### server
In tabeh user va pass az karbar migirad va dar beineh user database check mikonad agar vojood nadasht error midahad agar dasht check mikonad keh password dorost ast agar Ok bood yek authtoken bar asaseh srand() va rand() keh yek adadeh 24 raqami ast tolid mikonad va an ra dar yek file authtok.txt save mikonad (va barayeh har user dar yek khateh jadid albateh chon server ma faqat yek user dasht  dar 1 khat) va dar yek file user.txt dar har khat username ra minevisad dar karhayeh digar an ra khandeh va ba authtoken tatbiq midahad beh tori keh ba an authtoken user ra tashkhis midahad.

## mainmenu,main,chmenu (client)
In tavabeh dar client rabet beineh user va tavabeh digarand va karbord pass kardan darkhast va enteqali darand

## createch
### client
In tabeh az user name channel ra migirad va barayeh server mifrestad va natijeh ra beh user neshan midahad.
### server
In tabeh az client name channel ra migirad va agar qablan channel ba in name vojood nadasht yek channel create mikonad va user ra dar an ozv mikonad

## joinch
### client
In tabeh az user name channel ra migirad va barayeh server mifrestad va natijeh ra beh user neshan midahad.
### server
In tabeh az client name channel ra migirad va authtoken ra check mikonad agar qablan channel ba in name vojood nadasht yek error mifrestad dar qeir in soorat karbar ra ozv channel mikonad va karbar mitavanad message hayeh in channel ra moshahedeh konad

## chmembers
### client
In tabeh yek darkhast barayeh server mifrestad va member hayeh yek chahnnel ra barayeh user namayesh midahad
### user
In tabeh list member ha ra bar asaseh tarikheh ozviat dar channel barayeh client mifrestad

## leavech
### client
In tabeh darkhasteh khorooj az yek channel ra barayeh server mifrestad va natijeh ra bar migardanad.
### server
Dar in tabeh ba barresi authtoken va etebar sanji an karbar ra az member hayeh channel mojood hazf mikonad va hamchenin name channel ra az radifeh channel name montasab beh user hazf mikonad.

## sendmessage
### client
In tabeh yek message ra az user migirad va beh server ersal mikonad va sepas natijeh ra bar migardanad.
### server
In tabeh ba barresi authtoken message ra dar channel marbooteh qarar midahad va natijeh ra beh client bar migardanad

## refresh
### client
In tabeh yek darkhast barayeh server mifrestad va tamam message haii ra keh user nadideh ast barayeh user namayesh midahad.
### user
In tabeh akharin jai marboot beh message ra keh karbar moshahedeh kardeh dar nazar migirad
va sepas tamam message hayeh baed an (seen nashodeh) ra be user namayesh midahad.

## logout
### client
In tabeh darkhasteh khorooj az hesab ra barayeh server mifrestad va natijeh ra bar migardanad keh agar dorost bood safheyeh register/login barayeh user namayesh dadeh mishavad.
### server
Dar in tabeh ba barresi authtoken va etebar sanji an karbar az hesab karbari biroon miaiad va safheyeh register/login namayesh dadeh mishavad va karbar az list user hayeh online dar user.txt
va hamchenin authtoken an az authtok.txt hazf shodeh
