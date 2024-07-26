#pragma once

#define LOCTEXT_NAMESPACE "PropertySection"

#define ADD_PROPERTY_SECTION(CategoryName) \
{ \
    FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(FName(TEXT("PropertyEditor"))); \
    TSharedRef<FPropertySection> Section = PropertyModule.FindOrCreateSection("Object", "Custom", LOCTEXT("Custom", "Custom")); \
    Section->AddCategory(CategoryName); \
}