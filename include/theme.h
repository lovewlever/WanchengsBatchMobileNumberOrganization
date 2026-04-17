#ifndef THEME_H
#define THEME_H

#include <string>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


// =======================
// Scheme
// =======================
struct Scheme {
    std::string primary;
    std::string surfaceTint;
    std::string onPrimary;
    std::string primaryContainer;
    std::string onPrimaryContainer;

    std::string secondary;
    std::string onSecondary;
    std::string secondaryContainer;
    std::string onSecondaryContainer;

    std::string tertiary;
    std::string onTertiary;
    std::string tertiaryContainer;
    std::string onTertiaryContainer;

    std::string error;
    std::string onError;
    std::string errorContainer;
    std::string onErrorContainer;

    std::string background;
    std::string onBackground;

    std::string surface;
    std::string onSurface;

    std::string surfaceVariant;
    std::string onSurfaceVariant;

    std::string outline;
    std::string outlineVariant;

    std::string shadow;
    std::string scrim;

    std::string inverseSurface;
    std::string inverseOnSurface;
    std::string inversePrimary;

    std::string primaryFixed;
    std::string onPrimaryFixed;
    std::string primaryFixedDim;
    std::string onPrimaryFixedVariant;

    std::string secondaryFixed;
    std::string onSecondaryFixed;
    std::string secondaryFixedDim;
    std::string onSecondaryFixedVariant;

    std::string tertiaryFixed;
    std::string onTertiaryFixed;
    std::string tertiaryFixedDim;
    std::string onTertiaryFixedVariant;

    std::string surfaceDim;
    std::string surfaceBright;

    std::string surfaceContainerLowest;
    std::string surfaceContainerLow;
    std::string surfaceContainer;
    std::string surfaceContainerHigh;
    std::string surfaceContainerHighest;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Scheme,
    primary, surfaceTint, onPrimary, primaryContainer, onPrimaryContainer,
    secondary, onSecondary, secondaryContainer, onSecondaryContainer,
    tertiary, onTertiary, tertiaryContainer, onTertiaryContainer,
    error, onError, errorContainer, onErrorContainer,
    background, onBackground,
    surface, onSurface,
    surfaceVariant, onSurfaceVariant,
    outline, outlineVariant,
    shadow, scrim,
    inverseSurface, inverseOnSurface, inversePrimary,
    primaryFixed, onPrimaryFixed, primaryFixedDim, onPrimaryFixedVariant,
    secondaryFixed, onSecondaryFixed, secondaryFixedDim, onSecondaryFixedVariant,
    tertiaryFixed, onTertiaryFixed, tertiaryFixedDim, onTertiaryFixedVariant,
    surfaceDim, surfaceBright,
    surfaceContainerLowest, surfaceContainerLow, surfaceContainer,
    surfaceContainerHigh, surfaceContainerHighest
    )

// =======================
// Palette（强类型）
// =======================
struct Palette {
    std::string _0;
    std::string _5;
    std::string _10;
    std::string _15;
    std::string _20;
    std::string _25;
    std::string _30;
    std::string _35;
    std::string _40;
    std::string _50;
    std::string _60;
    std::string _70;
    std::string _80;
    std::string _90;
    std::string _95;
    std::string _98;
    std::string _99;
    std::string _100;
};

inline void from_json(const json& j, Palette& p) {
#define GET(n) p._##n = j.value(#n, "")
    GET(0); GET(5); GET(10); GET(15); GET(20);
    GET(25); GET(30); GET(35); GET(40);
    GET(50); GET(60); GET(70); GET(80);
    GET(90); GET(95); GET(98); GET(99); GET(100);
#undef GET
}

// =======================
// Schemes（强类型）
// =======================
struct Schemes {
    Scheme light;
    Scheme lightMediumContrast;
    Scheme lightHighContrast;
    Scheme dark;
    Scheme darkMediumContrast;
    Scheme darkHighContrast;
};

inline void from_json(const json& j, Schemes& s) {
    s.light = j.at("light").get<Scheme>();
    s.lightMediumContrast = j.at("light-medium-contrast").get<Scheme>();
    s.lightHighContrast = j.at("light-high-contrast").get<Scheme>();
    s.dark = j.at("dark").get<Scheme>();
    s.darkMediumContrast = j.at("dark-medium-contrast").get<Scheme>();
    s.darkHighContrast = j.at("dark-high-contrast").get<Scheme>();
}

// =======================
// Palettes（强类型）
// =======================
struct Palettes {
    Palette primary;
    Palette secondary;
    Palette tertiary;
    Palette neutral;
    Palette neutralVariant;
};

inline void from_json(const json& j, Palettes& p) {
    p.primary = j.at("primary").get<Palette>();
    p.secondary = j.at("secondary").get<Palette>();
    p.tertiary = j.at("tertiary").get<Palette>();
    p.neutral = j.at("neutral").get<Palette>();
    p.neutralVariant = j.at("neutral-variant").get<Palette>();
}

// =======================
// Theme
// =======================
struct Theme {
    std::string description;
    std::string seed;

    std::map<std::string, std::string> coreColors;

    Schemes schemes;
    Palettes palettes;
};

inline void from_json(const json& j, Theme& t) {
    t.description = j.value("description", "");
    t.seed = j.value("seed", "");

    if (j.contains("coreColors")) {
        t.coreColors = j["coreColors"].get<std::map<std::string, std::string>>();
    }

    t.schemes = j.at("schemes").get<Schemes>();
    t.palettes = j.at("palettes").get<Palettes>();
}

#endif // THEME_H
