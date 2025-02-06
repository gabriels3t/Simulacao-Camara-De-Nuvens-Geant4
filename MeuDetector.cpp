#include "MeuDetector.hpp"

#include "G4Box.hh" // incluindo uma caixa
#include "G4Material.hh" // Incluindo material
#include "G4NistManager.hh" // Incluindo lista de material
#include "G4LogicalVolume.hh" // Incluindo a união entre a geometria com o material
#include "G4VPhysicalVolume.hh" // Incluindo para um volume físico
#include "G4PVPlacement.hh" // Incluindo para um volume físico
#include "CLHEP/Units/SystemOfUnits.h" // Incluindo sistema de unidade
#include "G4SubtractionSolid.hh" // Incluindo para poder subtrair sólidos
#include "G4Element.hh" // Incluindo para poder Criar elementos


G4VPhysicalVolume* MeuDetector::Construct(){
    // Materiais
    auto ar = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"); // criando ar
    auto vidro = G4NistManager::Instance()->FindOrBuildMaterial("G4_GLASS_PLATE"); // criando vidro
    //auto etanol = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER"); // criando etanol saturado (etanol puro)

    // Criar elementos químicos para o álcool
    auto *H = new G4Element("Hydrogen", "H", 1, 1.008 * CLHEP::g / CLHEP::mole);
    auto *C = new G4Element("Carbon", "C", 6, 12.01 * CLHEP::g / CLHEP::mole);
    auto *O = new G4Element("Oxygen", "O", 8, 16.00 * CLHEP::g / CLHEP::mole);

    // Definir o material etanol (C2H5OH)
    auto *etanol = new G4Material("Ethanol", 1.05 * CLHEP::g / CLHEP::cm3, 3);
    etanol->AddElement(C, 2);
    etanol->AddElement(H, 6);
    etanol->AddElement(O, 1);

    // Mundo do detector (quarto)
    auto quartoBox = new G4Box("quarto", 1.0*CLHEP::m, 1.0*CLHEP::m, 1.0*CLHEP::m); // O quarto tem 2 metros de lado (1 metro de cada lado do centro)
    auto logicalQuarto = new G4LogicalVolume(quartoBox, ar, "Quarto-Logico"); // volume lógico do quarto
    auto quartoFisico = new G4PVPlacement(0, {0, 0, 0}, logicalQuarto, "Quarto", 0, false, 0); // volume físico do quarto

    // Aquário (30 x 30 x 45 cm com espessura de 5mm)
    double larguraAquario = 30.0 * CLHEP::cm;
    double profundidadeAquario = 30.0 * CLHEP::cm;
    double alturaAquario = 45.0 * CLHEP::cm;
    double espessuraAquario = 5.0 * CLHEP::mm;

    // Construção do aquário externo (vidro)
    auto aquarioExterno = new G4Box("Aquario-Externo", larguraAquario/2, profundidadeAquario/2, alturaAquario/2);
    auto aquarioInterno = new G4Box("Aquario-Interno", larguraAquario/2 - espessuraAquario, profundidadeAquario/2 - espessuraAquario, alturaAquario/2 - espessuraAquario);
    auto aquarioParede = new G4SubtractionSolid("AquarioParede", aquarioExterno, aquarioInterno); // subtração do aquário interno para formar a parede

    // Construindo o volume lógico para o aquário externo (vidro)
    auto aquarioLogicoParede = new G4LogicalVolume(aquarioParede, vidro, "Aquario-Parede");

    // Colocando o aquário no espaço do quarto
    auto aquarioFisico = new G4PVPlacement(0, {0, 0, 0}, aquarioLogicoParede, "Aquario-Fisico", logicalQuarto, false, 0);

    // Criando o volume interno para o etanol (dentro do aquário)
    auto aquarioLogicoEtanol = new G4LogicalVolume(aquarioInterno, etanol, "Aquario-Logico-Etanol");

    // Agora, associamos o material ao volume lógico do etanol
    if (!etanol) {
        G4Exception("MeuDetector::Construct", "InvalidMaterial", JustWarning, "Etanol não encontrado. Verifique a configuração do material.");
    }

    // Colocando o etanol dentro do aquário
    auto aquarioFisicoEtanol = new G4PVPlacement(0, {0, 0, 0}, aquarioLogicoEtanol, "Aquario-Fisico-Etanol", logicalQuarto, false, 0);

    return quartoFisico; // Retorna o volume físico do quarto, que inclui o aquário e etanol
}
