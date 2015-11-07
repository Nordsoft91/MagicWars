//
//  FlaredEnum.h
//  MagicWars
//
//  Created by nordsoft on 28.10.15.
//
//

#ifndef __MagicWars__FlaredEnum__
#define __MagicWars__FlaredEnum__

#include <string>

#define RULE_MAKER_STR(x,y,z) std::string(x) + std::string(y) + std::string(z)

#define RULE_MAKER_TERRAIN  Flared_NS::RuleSimpleChange ruleMakerSimpleChange; \
                            Flared_NS::RuleTerrainCenter ruleMakerTerrainCenter; \
                            Flared_NS::RuleTerrainEdge ruleMakerTerrainEdge; \
                            Flared_NS::RuleTerrainCorner ruleMakerTerrainCorner; \
                            Flared_NS::RuleTerrainInsideCorner ruleMakerTerrainInsideCorner;

#define RULE_MAKER_REGISTER(class, x)   class.registerRule(ruleMakerTerrainCenter.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_center") )); \
                                        class.registerRule(ruleMakerTerrainEdge.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_edge_right") )); \
                                        class.registerRule(ruleMakerTerrainEdge.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_edge_left") )); \
                                        class.registerRule(ruleMakerTerrainEdge.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_edge_top") )); \
                                        class.registerRule(ruleMakerTerrainEdge.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_edge_bottom") )); \
                                        class.registerRule(ruleMakerTerrainCorner.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_corner_right") )); \
                                        class.registerRule(ruleMakerTerrainCorner.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_corner_left") )); \
                                        class.registerRule(ruleMakerTerrainCorner.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_corner_top") )); \
                                        class.registerRule(ruleMakerTerrainCorner.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_corner_bottom") )); \
                                        class.registerRule(ruleMakerTerrainInsideCorner.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_insidecorner_right") )); \
                                        class.registerRule(ruleMakerTerrainInsideCorner.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_insidecorner_left") )); \
                                        class.registerRule(ruleMakerTerrainInsideCorner.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_insidecorner_top") )); \
                                        class.registerRule(ruleMakerTerrainInsideCorner.makeRuleFromConsts( RULE_MAKER_STR("rule_",x,"_insidecorner_bottom") ));

namespace Flared_NS {
    
    enum class Orientation
    {
        Orthogonal
    };
}

#endif /* defined(__MagicWars__FlaredEnum__) */
