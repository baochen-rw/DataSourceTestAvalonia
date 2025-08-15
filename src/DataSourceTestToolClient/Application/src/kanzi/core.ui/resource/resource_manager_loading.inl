// Copyright 2008-2021 by Rightware. All rights reserved.

/// Loads timeline sequence from resource manager.
#include <kanzi/core.ui/animation/timeline_resource.hpp>
#include <kanzi/core.ui/resource/resource_dictionary_selector.hpp>

#ifdef KANZI_FEATURE_3D
#include <kanzi/core.ui/graphics3d/mesh_create_info.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/shader_create_info.hpp>
#endif

#include <kanzi/core.ui/font/kzu_font_base.h>

/// Loads a timeline resource from the given KZB stream/file.
static kanzi::ResourceSharedPtr loadTimeline(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::TimelineResourceSharedPtr timelineResource = kanzi::TimelineResource::create(domain, kzuBinaryFileInfoGetName(file));

    timelineResource->loadFromKZBWithoutContext(inputStream, file);

    return timelineResource;
}

/** Loads style from resource manager. */
static kanzi::StyleSharedPtr kzuResourceManagerLoadStyle_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::Style* style = kanzi::Style::createEmpty(domain, kzuBinaryFileInfoGetName(file));
    style->setNotLoaded();
    style->loadFromKZB(0, inputStream, file);

    return kanzi::make_polymorphic_shared_ptr<kanzi::Resource>(style);
}

/** Loads font from resource manager. */
static kanzi::FontSharedPtr kzuResourceManagerLoadFont_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kzsError result;
    KzcMemoryManager* memoryManager = domain->getMemoryManager();
    KzuTextRenderer* textRenderer = domain->getTextRenderer();
    kzString name = kzuBinaryFileInfoGetName(file);

    KzuFont* font;

    switch (kzuBinaryFileInfoGetType(file))
    {
        case KZU_BINARY_FILE_TYPE_BITMAP_FONT:
        {
#ifdef KANZI_FEATURE_3D
            KzuBitmapFontSystem* fontSystem;
            KzuBitmapFont* bitmapFont;

            result = kzuTextRendererGetBitmapFontSystem(textRenderer, &fontSystem);
            kzThrowIfError(result);

            result = kzuBitmapFontCreate(fontSystem, domain, name, &bitmapFont);
            kzThrowIfError(result);

            font = kzuBitmapFontToFont(bitmapFont);
#else
            kzAssertUnreachable();
#endif
            break;
        }

        case KZU_BINARY_FILE_TYPE_TRUETYPE_FONT:
        {
            KzuTruetypeSystem* fontSystem;

            result = kzuTextRendererGetTruetypeSystem(textRenderer, &fontSystem);
            kzThrowIfError(result);

            result = kzuTruetypeSystemCreateFont(memoryManager, fontSystem, name, &font);
            kzThrowIfError(result);

            break;
        }

        default:
        {
            kanzi::kzThrowLegacyErrorFormat(KZU_ERROR_WRONG_BINARY_FILE_TYPE,
                "Wrong file type %d encountered while trying to load font file '%s'.",
                (kzInt)kzuBinaryFileInfoGetType(file), kzuBinaryFileInfoGetName(file));
        }
    }

    result = kzuFontLoadFromKZB(font, inputStream, file);
    kzThrowIfError(result);

    return kanzi::make_polymorphic_shared_ptr<kanzi::Resource>(font);
}

/** Loads material from resource manager. */
static kanzi::MaterialSharedPtr kzuResourceManagerLoadMaterial_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::Material* material = kanzi::Material::createEmpty(domain, kzuBinaryFileInfoGetName(file));
    material->setNotLoaded();
    material->loadFromKZB(0, inputStream, file);

    return kanzi::make_polymorphic_shared_ptr<kanzi::Resource>(material);
}

/** Loads object source from resource manager. */
static kanzi::ObjectSourceSharedPtr kzuResourceManagerLoadObjectSource_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kzsException result;
    KzcMemoryManager* memoryManager = domain->getMemoryManager();
    KzuObjectSource* objectSource;

    kzString name = kzuBinaryFileInfoGetName(file);

    kzInt type;
    result = kzcInputStreamReadS32Int(inputStream, (kzInt*)&type);
    kzThrowIfError(result);

    /* Create and load the object source. */
    switch (type)
    {
        case 0: /* Root. */
        {
            kanzi::kzThrowLegacyErrorFormat(KZS_ERROR_ENUM_OUT_OF_RANGE, "Root object sources no longer supported in .KZB (file '%s')", name);
        }

#ifdef KANZI_FEATURE_3D

        case 10: /* Combine. */
        {
            result = kzuCombinerObjectSourceCreate(domain, name, &objectSource);
            kzThrowIfError(result);

            result = kzuCombinerObjectSourceLoadFromKZB(objectSource, inputStream, file);
            kzThrowIfError(result);

            break;
        }

        case 50: /* Fixed sorter. */
        {
            objectSource = kzuSortObjectSourceCreate(domain, name);

            result = kzuSortObjectSourceLoadFromKZB(objectSource, inputStream, file);
            kzThrowIfError(result);

            break;
        }

        case 103: /* Filter contains property. */
        {
            result = kzuContainsPropertyFilterCreate(domain, name, &objectSource);
            kzThrowIfError(result);

            result = kzuContainsPropertyFilterLoadFromKZB(objectSource, inputStream, file);
            kzThrowIfError(result);

            break;
        }

        case 104: /* Object type. */
        {
            objectSource = kzuObjectTypeFilterCreate(domain, name);

            result = kzuObjectTypeFilterLoadFromKZB(objectSource, inputStream, file);
            kzThrowIfError(result);

            break;
        }

        case 105: /* Is equal. */
        {
            result = kzuPropertyIsEqualFilterCreate(memoryManager, domain, name, &objectSource);
            kzThrowIfError(result);

            result = kzuPropertyIsEqualFilterLoadFromKZB(objectSource, inputStream, file);
            kzThrowIfError(result);

            break;
        }

        case 106: /* Tag filter. */
        {
            objectSource = kzuTagFilterCreate(memoryManager, domain, name);

            result = kzuTagFilterLoadFromKZB(objectSource, inputStream, file);
            kzThrowIfError(result);

            break;
        }

#endif

        default:
        {
            kanzi::kzThrowLegacyErrorFormat(KZS_ERROR_ENUM_OUT_OF_RANGE,
                "Invalid object source binary type %d in file '%s'", type, name);
        }
    }

    return kanzi::make_polymorphic_shared_ptr<kanzi::Resource>(objectSource);
}

/** Loads trajectory from resource manager. */
static kanzi::TrajectorySharedPtr kzuResourceManagerLoadTrajectory_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::Trajectory* trajectory = kanzi::Trajectory::createEmpty(domain, kzuBinaryFileInfoGetName(file));
    trajectory->setNotLoaded();
    trajectory->loadFromKZB(0, inputStream, file);

    return kanzi::make_polymorphic_shared_ptr<kanzi::Resource>(trajectory);
}

/** Loads state manager from resource manager. */
static kanzi::StateManagerSharedPtr kzuResourceManagerLoadStateManager_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::StateManager* stateManager = kanzi::StateManager::createEmpty(domain, kzuBinaryFileInfoGetName(file));

    stateManager->setNotLoaded();
    stateManager->loadFromKZB(0, inputStream, file);

    return kanzi::make_polymorphic_shared_ptr<kanzi::Resource>(stateManager);
}

/** Loads prefab template from resource manager. */
static kanzi::PrefabTemplateSharedPtr kzuResourceManagerLoadPrefabTemplate_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kzsException result;
    kanzi::PrefabTemplate* prefabTemplate;

    result = kzuPrefabTemplateCreate(domain, kzuBinaryFileInfoGetName(file), &prefabTemplate);
    kzThrowIfError(result);

    result = kzuPrefabTemplateLoadFromKZB(prefabTemplate, inputStream, file);
    kzThrowIfError(result);

    return kanzi::make_polymorphic_shared_ptr<kanzi::Resource>(prefabTemplate);
}

/** Loads material from resource manager. */
static kanzi::ResourceSharedPtr kzuResourceManagerLoadPrefabTemplateNode_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kzsError result;
    kanzi::PrefabTemplateNodeSharedPtr prefabTemplateNode;
    const kanzi::Metaclass* objectType = 0;
    kanzi::PrefabTemplateSharedPtr prefabTemplate;
    KzuBinaryFileType binaryFileType = kzuBinaryFileInfoGetType(file);
    enum TemplateNodeType
    {
        TYPED, PLACEHOLDER
    } templateNodeType = TYPED;

    kanzi::ObjectFactory* objectFactory = domain->getObjectFactory();

    switch (binaryFileType)
    {
#ifdef KANZI_FEATURE_3D
        case KZU_BINARY_FILE_TYPE_EMPTY_NODE: objectType = kanzi::EmptyNode3D::getStaticMetaclass(); break;
        case KZU_BINARY_FILE_TYPE_MESH_NODE: objectType = kanzi::Model3D::getStaticMetaclass(); break;
        case KZU_BINARY_FILE_TYPE_CAMERA_NODE: objectType = kanzi::Camera::getStaticMetaclass(); break;
        case KZU_BINARY_FILE_TYPE_LIGHT_NODE: objectType = kanzi::Light::getStaticMetaclass(); break;
        case KZU_BINARY_FILE_TYPE_LOD_SELECTOR_NODE: objectType = kanzi::LevelOfDetail3D::getStaticMetaclass(); break;
        case KZU_BINARY_FILE_TYPE_INSTANTIATOR_NODE: objectType = kanzi::Instantiator3D::getStaticMetaclass(); break;
        case KZU_BINARY_FILE_TYPE_SCENE: objectType = kanzi::Scene::getStaticMetaclass(); break;
#endif
        case KZU_BINARY_FILE_TYPE_SCREEN: objectType = kanzi::Screen::getStaticMetaclass(); break;
        case KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE:
        case KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE_2D:
        {
            kanzi::string metaclassName = kzuBinaryReadString(inputStream);

            const kanzi::Metaclass* metaclass = objectFactory->getMetaclass(metaclassName);
            if (metaclass)
            {
                objectType = metaclass;
            }
            else
            {
                kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Requested node type '{}' in file '{}' was not registered to engine.", metaclassName, kanzi::string_view(kzuBinaryFileInfoGetName(file))));

#ifdef KANZI_FEATURE_3D
                objectType = (binaryFileType == KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE) ? kanzi::EmptyNode3D::getStaticMetaclass() : kanzi::EmptyNode2D::getStaticMetaclass();
#else
                kzAssert(binaryFileType != KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE);
                objectType = EmptyNode2D::getStaticMetaclass();
#endif
            }

            templateNodeType = TYPED;

            break;
        }

        case KZU_BINARY_FILE_TYPE_LAYER:
        {
            kanzi::string metaclassName = kzuBinaryReadString(inputStream);

            const kanzi::Metaclass* metaclass = objectFactory->getMetaclass(metaclassName);
            if (metaclass)
            {
                objectType = metaclass;
            }
            else
            {
                kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Requested 2d node type '{}' in file '{}' was not registered to engine.", metaclassName, kanzi::string_view(kzuBinaryFileInfoGetName(file))));

                objectType = kanzi::EmptyNode2D::getStaticMetaclass();
            }

            templateNodeType = TYPED;

            break;
        }

        case KZU_BINARY_FILE_TYPE_PREFAB_OBJECT_PLACEHOLDER:
        case KZU_BINARY_FILE_TYPE_PREFAB_LAYER_PLACEHOLDER:
        {
            switch (kzuBinaryFileInfoGetType(file))
            {
#ifdef KANZI_FEATURE_3D
                case KZU_BINARY_FILE_TYPE_PREFAB_OBJECT_PLACEHOLDER: objectType = kanzi::EmptyNode3D::getStaticMetaclass(); break;
#endif
                case KZU_BINARY_FILE_TYPE_PREFAB_LAYER_PLACEHOLDER: objectType = kanzi::EmptyNode2D::getStaticMetaclass(); break;
                default:
                {
                    kzAssertUnreachable();
                }
            }

            kanzi::string prefabTemplateURL = kzuBinaryReadString(inputStream);
            if (!prefabTemplateURL.empty())
            {
                kanzi::ResourceManager* resourceManager = domain->getResourceManager();
                
                prefabTemplate = domain->isEditingEnabled() ? 
                    resourceManager->tryAcquireResource<kanzi::PrefabTemplate>(prefabTemplateURL) :
                    resourceManager->acquireResource<kanzi::PrefabTemplate>(prefabTemplateURL);
                
                if (prefabTemplate)
                {
                    /* This function may load the object node as well as a side effect. */
                    if (kzuPrefabTemplateGetRoot(prefabTemplate.get()) != KZ_NULL)
                    {
                        templateNodeType = PLACEHOLDER;
                    }
                }
                else
                {
                    kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("'{}' failed to load prefab template from kzb-url: '{}'.", kanzi::string_view(kzuBinaryFileInfoGetName(file)), prefabTemplateURL));
                    kzAssert(domain->isEditingEnabled());
                }
            }
            break;
        }

        default:
        {
            kanzi::kzThrowLegacyErrorFormat(KZU_ERROR_WRONG_BINARY_FILE_TYPE,
                "Invalid file type %d encountered while trying to load object node file '%s'.",
                (kzInt)kzuBinaryFileInfoGetType(file), kzuBinaryFileInfoGetName(file));
        }
    }

    {
        kzString realPath = kzuBinaryFileInfoGetPath(file);

        kzAssert(objectType != KZ_NULL);

        switch (templateNodeType)
        {
            case TYPED:
            {
                prefabTemplateNode = kzuPrefabTemplateNodeCreateTyped(domain, objectType, realPath, kzuBinaryFileInfoGetName(file));
                break;
            }

            case PLACEHOLDER:
            {
                prefabTemplateNode = kzuPrefabTemplateNodeCreatePlaceholder(domain, prefabTemplate, realPath, kzuBinaryFileInfoGetName(file));
                break;
            }

            default:
            {
                kanzi::kzThrowLegacyErrorFormat(KZS_ERROR_ENUM_OUT_OF_RANGE,
                    "Invalid prefab template node type %d in file '%s'.",
                    (kzInt)templateNodeType, kzuBinaryFileInfoGetName(file));
            }
        }

        result = kzuPrefabTemplateNodeLoadChildrenFromKZB(prefabTemplateNode.get(), inputStream, file);
        kzThrowIfError(result);

        kzuPrefabTemplateNodeLoad(prefabTemplateNode.get(), inputStream, file);
    }

    return prefabTemplateNode;
}

/** Loads brush from resource manager. */
static kanzi::BrushSharedPtr kzuResourceManagerLoadBrush_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    uint32_t keepAliveInt = kzuBinaryReadU32(inputStream);
    bool keepAlive = keepAliveInt != 0;

    kanzi::BrushSharedPtr brush;
    kanzi::string brushType(kzuBinaryReadString(inputStream));

    if(brushType == "Kanzi.ColorBrush")
    {
        brush = kanzi::ColorBrush::create(domain, kzuBinaryFileInfoGetName(file));
    }
    else if(brushType == "Kanzi.ContentBrush")
    {
        brush = kanzi::ContentBrush::create(domain, kzuBinaryFileInfoGetName(file));
    }
    else if(brushType == "Kanzi.ShaderBrush")
    {
        kzThrowException(kanzi::runtime_error("brush type '" + brushType + "' not implemented yet"));
    }
    else if(brushType == "Kanzi.TextureBrush")
    {
        brush = kanzi::TextureBrush::create(domain, kzuBinaryFileInfoGetName(file));
    }
    else if(brushType == "Kanzi.MaterialBrush")
    {
        brush = kanzi::MaterialBrush::create(domain, kzuBinaryFileInfoGetName(file));
    }
    else
    {
        kzThrowException(kanzi::runtime_error("invalid brush type '" + brushType + "'"));
    }

    brush->load(inputStream, file);

    brush->setKeepAlive(keepAlive);

    return brush;
}

#ifdef KANZI_FEATURE_3D

static kanzi::MorphSharedPtr kzuResourceManagerLoadMorph_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::MorphSharedPtr morph = kanzi::Morph::create(domain, kzuBinaryFileInfoGetName(file));
    morph->setNotLoaded();
    morph->loadFromKZB(0, inputStream, file);
    return morph;
}

#endif

/** Loads resource dictionary from resource manager. */
static kanzi::ResourceDictionarySharedPtr kzuResourceManagerLoadResourceDictionary_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::ResourceDictionarySharedPtr resourceDictionary = kanzi::ResourceDictionary::create(domain, kzuBinaryFileInfoGetName(file));

    resourceDictionary->load(inputStream, file);

    return resourceDictionary;
}

/** Loads resource dictionary selector from resource manager. */
static kanzi::ResourceDictionarySelectorSharedPtr kzuResourceManagerLoadResourceDictionarySelector_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::ResourceDictionarySelectorSharedPtr resourceDictionary = kanzi::ResourceDictionarySelector::create(domain, kzuBinaryFileInfoGetName(file));

    resourceDictionary->load(inputStream, file);

    return resourceDictionary;
}

/** Loads generic file from resource manager. */
static kanzi::BinaryResourceSharedPtr kzuResourceManagerLoadGenericFile_internal(kanzi::Domain* domain, KzcInputStream* inputStream, const KzuBinaryFileInfo* file)
{
    kanzi::BinaryResource* binaryResource = kanzi::BinaryResource::createEmpty(domain, kzuBinaryFileInfoGetName(file));
    binaryResource->setNotLoaded();
    binaryResource->loadFromKZBWithoutContext(inputStream, file);

    return kanzi::make_polymorphic_shared_ptr<kanzi::Resource>(binaryResource);
}

namespace kanzi
{

#ifdef KANZI_FEATURE_3D

struct ShaderLoadTask : public ResourceManager::LoadTask
{
    Domain* m_domain;
    const KzuBinaryDirectory* m_directory;
    const KzuBinaryFileInfo* m_file;
    ShaderProgram::CreateInfo m_loadData;
    bool m_keepAlive;
    ShaderProgramSharedPtr m_result;

    explicit ShaderLoadTask(Domain* domain, const KzuBinaryDirectory* directory, const KzuBinaryFileInfo* file) :
        ResourceManager::LoadTask(ResourceManager::LoadTask::LoadAndFinish),
        m_domain(domain),
        m_directory(directory),
        m_file(file),
        m_keepAlive(false)
    {
    }

    virtual void loadFunction(const ResourceLoaderThreadContext* /*threadContext*/) KZ_OVERRIDE
    {
        kzsError result;
        KzcInputStream* inputStream;
        KzcMemoryManager* memoryManager = m_domain->getMemoryManager();

        result = kzuBinaryDirectoryOpenFile(memoryManager, m_file, &inputStream);
        kzThrowIfError(result);

        uint32_t keepAliveInt = kzuBinaryReadU32(inputStream);
        m_keepAlive = keepAliveInt != 0;

        ShaderProgram::CreateInfo loadData = loadShaderProgramCreateInfo(m_domain, inputStream, m_file);
        swap(loadData, m_loadData);

        result = kzcInputStreamDelete(inputStream);
        kzThrowIfError(result);
    }

    virtual void finishFunction(const ResourceLoaderThreadContext* /*threadContext*/) KZ_OVERRIDE
    {
        kzString name = kzuBinaryFileInfoGetName(m_file);
        m_result = ShaderProgram::create(m_domain, m_loadData, name);

        m_result->setKeepAlive(m_keepAlive);

        kzString path = kzuBinaryFileInfoGetPath(m_file);
        m_result->setKZB(m_directory, path);
    }

    virtual ResourceSharedPtr getResult() KZ_OVERRIDE
    {
        return m_result;
    }
};

struct MeshLoadTask : public ResourceManager::LoadTask
{
    Domain* m_domain;
    const KzuBinaryDirectory* m_directory;
    const KzuBinaryFileInfo* m_file;
    Mesh::CreateInfo m_createInfo;
    bool m_keepAlive;
    MeshSharedPtr m_result;

    explicit MeshLoadTask(Domain* domain, const KzuBinaryDirectory* directory, const KzuBinaryFileInfo* file) :
        ResourceManager::LoadTask(ResourceManager::LoadTask::LoadAndFinish),
        m_domain(domain),
        m_directory(directory),
        m_file(file),
        m_keepAlive(false)
    {
    }

    virtual void loadFunction(const ResourceLoaderThreadContext* /*threadContext*/) KZ_OVERRIDE
    {
        kzsError result;
        KzcInputStream* inputStream;
        KzcMemoryManager* memoryManager = m_domain->getMemoryManager();

        result = kzuBinaryDirectoryOpenFile(memoryManager, m_file, &inputStream);
        kzThrowIfError(result);

        uint32_t keepAliveInt = kzuBinaryReadU32(inputStream);
        m_keepAlive = keepAliveInt != 0;

        Mesh::CreateInfo createInfo = loadMeshCreateInfo(m_domain, inputStream, m_file);
        swap(createInfo, m_createInfo);

        result = kzcInputStreamDelete(inputStream);
        kzThrowIfError(result);
    }

    virtual void finishFunction(const ResourceLoaderThreadContext* /*threadContext*/) KZ_OVERRIDE
    {
        acquireResources(m_domain, m_createInfo);

        kzString name = kzuBinaryFileInfoGetName(m_file);
        m_result = Mesh::create(m_domain, m_createInfo, name);

        m_result->setKeepAlive(m_keepAlive);

        kzString path = kzuBinaryFileInfoGetPath(m_file);
        m_result->setKZB(m_directory, path);
    }

    virtual ResourceSharedPtr getResult() KZ_OVERRIDE
    {
        return m_result;
    }
};

struct TextureLoadTask : public ResourceManager::LoadTask
{
    Domain* m_domain;
    const KzuBinaryDirectory* m_directory;
    const KzuBinaryFileInfo* m_file;
    Texture::CreateInfo m_createInfo;
    bool m_keepAlive;
    TextureSharedPtr m_result;

    explicit TextureLoadTask(Domain* domain, const KzuBinaryDirectory* directory, const KzuBinaryFileInfo* file) :
        ResourceManager::LoadTask(ResourceManager::LoadTask::LoadAndFinish),
        m_domain(domain),
        m_directory(directory),
        m_file(file),
        m_keepAlive(false)
    {
    }

    virtual void loadFunction(const ResourceLoaderThreadContext* /*threadContext*/) KZ_OVERRIDE
    {
        kzsError result;
        KzcInputStream* inputStream;
        KzcMemoryManager* memoryManager = m_domain->getMemoryManager();

        result = kzuBinaryDirectoryOpenFile(memoryManager, m_file, &inputStream);
        kzThrowIfError(result);

        uint32_t keepAliveInt = kzuBinaryReadU32(inputStream);
        m_keepAlive = keepAliveInt != 0;

        Texture::CreateInfo createInfo = loadTextureCreateInfo(m_domain, inputStream, m_file);
        swap(createInfo, m_createInfo);

        result = kzcInputStreamDelete(inputStream);
        kzThrowIfError(result);
    }

    virtual void finishFunction(const ResourceLoaderThreadContext* /*threadContext*/) KZ_OVERRIDE
    {
        kzString name = kzuBinaryFileInfoGetName(m_file);

        Renderer* renderer = m_domain->getRenderer();
        bool deployRequested = (m_createInfo.memoryType == GPUResource::GpuOnly) || (m_createInfo.memoryType == GPUResource::GpuAndRam);
        Texture::CreateInfo::Status status = m_createInfo.adjust(*renderer, name);
        if (status == Texture::CreateInfo::StatusValid)
        {
            m_result = Texture::create(m_domain, m_createInfo, name);

            m_result->setKeepAlive(m_keepAlive);

            // Texture::create() will also deploy the texture if memory type in
            // CreateInfo includes Gpu. Texture deployment can still fail for
            // example if GPU is running out of memory. As result the texture
            // we get here might not be useful; isDeployed() can still return
            // false.
            Surface* surface = m_result.get();
            if (deployRequested && !surface->isDeployed())
            {
                kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Failed to deploy texture '{}'.", string_view(name)));
                Texture::CreateInfo createInfo = Texture::CreateInfo::createSubstitutePattern(*renderer, m_createInfo.type);
                m_result = Texture::create(m_domain, createInfo, name);
            }
            else
            {
                kzString path = kzuBinaryFileInfoGetPath(m_file);
                m_result->setKZB(m_directory, path);
            }
        }
        else
        {
            kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Failed to load texture '{}': {}", string_view(name), getVerboseDescription(status)));
            Texture::CreateInfo createInfo = Texture::CreateInfo::createSubstitutePattern(*renderer, m_createInfo.type);
            m_result = Texture::create(m_domain, createInfo, name);
        }
    }

    virtual ResourceSharedPtr getResult() KZ_OVERRIDE
    {
        return m_result;
    }
};

#endif

void ResourceManager::loadResourceFile(const KzuBinaryDirectory* directory, const KzuBinaryFileInfo* file,
    ResourceSharedPtr& out_resource, LoadTaskSharedPtr& out_loadTask)
{
    debugCheckMainThread();

    kzsError result;
    Domain* domain = m_domain;
    ResourceSharedPtr resource;
    LoadTaskSharedPtr loadTask;
    bool isShader = false;
    bool isMesh = false;
    bool isTexture = false;

    KzuBinaryFileType fileType = kzuBinaryFileInfoGetType(file);
    kzString name = kzuBinaryFileInfoGetName(file);
    switch (fileType)
    {
        case KZU_BINARY_FILE_TYPE_MESH:
        case KZU_BINARY_FILE_TYPE_MESH_BOX:
        case KZU_BINARY_FILE_TYPE_MESH_PLANE:
        case KZU_BINARY_FILE_TYPE_MESH_SPHERE:
        case KZU_BINARY_FILE_TYPE_SHADER_PROGRAM:
        case KZU_BINARY_FILE_TYPE_TEXTURE:
        {
            switch (fileType)
            {
                case KZU_BINARY_FILE_TYPE_MESH:
                case KZU_BINARY_FILE_TYPE_MESH_BOX:
                case KZU_BINARY_FILE_TYPE_MESH_PLANE:
                case KZU_BINARY_FILE_TYPE_MESH_SPHERE:
                {
                    isMesh = true;
                    break;
                }

                case KZU_BINARY_FILE_TYPE_SHADER_PROGRAM:
                {
                    isShader = true;
                    break;
                }

                case KZU_BINARY_FILE_TYPE_TEXTURE:
                {
                    isTexture = true;
                    break;
                }

                default:
                {
                    kzAssertUnreachable();
                }
            }

            break;
        }

        case KZU_BINARY_FILE_TYPE_TIMELINE_SEQUENCE:
        case KZU_BINARY_FILE_TYPE_ANIMATION_DATA:
        case KZU_BINARY_FILE_TYPE_ANIMATION_CLIP:
        case KZU_BINARY_FILE_TYPE_ANIMATION_CHILD_CLIP:
        case KZU_BINARY_FILE_TYPE_STYLE:
        case KZU_BINARY_FILE_TYPE_COMPOSER:
        case KZU_BINARY_FILE_TYPE_RENDERPASS:
        case KZU_BINARY_FILE_TYPE_MATERIAL:
        case KZU_BINARY_FILE_TYPE_TRAJECTORY:
        case KZU_BINARY_FILE_TYPE_OBJECT_SOURCE:
        case KZU_BINARY_FILE_TYPE_BITMAP_FONT:
        case KZU_BINARY_FILE_TYPE_TRUETYPE_FONT:
        case KZU_BINARY_FILE_TYPE_STATE_MANAGER:
        case KZU_BINARY_FILE_TYPE_PREFAB_TEMPLATE:
        case KZU_BINARY_FILE_TYPE_EMPTY_NODE:
        case KZU_BINARY_FILE_TYPE_MESH_NODE:
        case KZU_BINARY_FILE_TYPE_CAMERA_NODE:
        case KZU_BINARY_FILE_TYPE_LIGHT_NODE:
        case KZU_BINARY_FILE_TYPE_LOD_SELECTOR_NODE:
        case KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE:
        case KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE_2D:
        case KZU_BINARY_FILE_TYPE_LAYER:
        case KZU_BINARY_FILE_TYPE_INSTANTIATOR_NODE:
        case KZU_BINARY_FILE_TYPE_SCENE:
        case KZU_BINARY_FILE_TYPE_PREFAB_OBJECT_PLACEHOLDER:
        case KZU_BINARY_FILE_TYPE_PREFAB_LAYER_PLACEHOLDER:
        case KZU_BINARY_FILE_TYPE_SCREEN:
        case KZU_BINARY_FILE_TYPE_BINARY:
        case KZU_BINARY_FILE_TYPE_SCRIPT:
        case KZU_BINARY_FILE_TYPE_BRUSH:
        case KZU_BINARY_FILE_TYPE_RESOURCE_DICTIONARY:
        case KZU_BINARY_FILE_TYPE_RESOURCE_DICTIONARY_SELECTOR:
        case KZU_BINARY_FILE_TYPE_MORPH:
        case KZU_BINARY_FILE_TYPE_DATA_SOURCE:
        case KZU_BINARY_FILE_TYPE_PAGE_TRANSITION_COLLECTION:
        {
            KzcMemoryManager* memoryManager = domain->getMemoryManager();
            KzcInputStream* inputStream;

            /* Open the file, load it and close the input stream. */
            result = kzuBinaryDirectoryOpenFile(memoryManager, file, &inputStream);
            kzThrowIfError(result);

            switch (fileType)
            {
                case KZU_BINARY_FILE_TYPE_STYLE:
                {
                    resource = kzuResourceManagerLoadStyle_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_COMPOSER:
                {
                    string metaclassName = kzuBinaryReadString(inputStream);
                    const Metaclass* metaclass = domain->getObjectFactory()->getMetaclass(metaclassName);
                    if (metaclass)
                    {
                        resource = metaclass->create<Resource>(domain, name);
                        resource->setNotLoaded();
                        resource->loadFromKZB(&m_mainThreadContext, inputStream, file);
                    }
                    else
                    {
                        kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Requested composer type '{}' in file '{}' was not registered to engine.", metaclassName, string_view(name)));
                    }
                    break;
                }

                case KZU_BINARY_FILE_TYPE_RENDERPASS:
                {
                    string metaclassName = kzuBinaryReadString(inputStream);
                    const Metaclass* metaclass = domain->getObjectFactory()->getMetaclass(metaclassName);
                    if (metaclass)
                    {
                        resource = metaclass->create<Resource>(domain, name);
                        resource->setNotLoaded();
                        resource->loadFromKZB(&m_mainThreadContext, inputStream, file);
                    }
                    else
                    {
                        kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Requested renderpass type '{}' in file '{}' was not registered to engine.", metaclassName, string_view(name)));
                    }
                    break;
                }

                case KZU_BINARY_FILE_TYPE_TIMELINE_SEQUENCE:
                {
                    resource = loadTimeline(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_ANIMATION_CHILD_CLIP:
                {
                    resource = loadTimeline(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_ANIMATION_CLIP:
                {
                    resource = loadTimeline(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_ANIMATION_DATA:
                {
                    resource = loadTimeline(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_MATERIAL:
                {
                    resource = kzuResourceManagerLoadMaterial_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_TRAJECTORY:
                {
                    resource = kzuResourceManagerLoadTrajectory_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_OBJECT_SOURCE:
                {
                    resource = kzuResourceManagerLoadObjectSource_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_BITMAP_FONT:
                case KZU_BINARY_FILE_TYPE_TRUETYPE_FONT:
                {
                    resource = kzuResourceManagerLoadFont_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_STATE_MANAGER:
                {
                    resource = kzuResourceManagerLoadStateManager_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_PREFAB_TEMPLATE:
                {
                    resource = kzuResourceManagerLoadPrefabTemplate_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_SCRIPT:
                {
                    resource = kzuResourceManagerLoadGenericFile_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_BRUSH:
                {
                    resource = kzuResourceManagerLoadBrush_internal(domain, inputStream, file);
                    break;
                }

#ifdef KANZI_FEATURE_3D
                case KZU_BINARY_FILE_TYPE_MORPH:
                {
                    resource = kzuResourceManagerLoadMorph_internal(domain, inputStream, file);
                    break;
                }
#endif

                case KZU_BINARY_FILE_TYPE_RESOURCE_DICTIONARY:
                {
                    resource = kzuResourceManagerLoadResourceDictionary_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_RESOURCE_DICTIONARY_SELECTOR:
                {
                    resource = kzuResourceManagerLoadResourceDictionarySelector_internal(domain, inputStream, file);
                    break;
                }

                case KZU_BINARY_FILE_TYPE_DATA_SOURCE:
                {
                    string metaclassName = kzuBinaryReadString(inputStream);

                    const Metaclass* metaclass = domain->getObjectFactory()->getMetaclass(metaclassName);
                    if (metaclass)
                    {
                        resource = metaclass->create<Resource>(domain, name);
                        resource->setNotLoaded();
                        resource->setKZB(kzuBinaryFileInfoGetDirectory(file), kzuBinaryFileInfoGetPath(file));
                        resource->load();
                    }
                    else
                    {
                        kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Requested data source type '{}' in file '{}' was not registered to engine.", metaclassName, string_view(name)));

                        resource = DataSource::create(domain, name);
                    }
                    break;
                }

                case KZU_BINARY_FILE_TYPE_PAGE_TRANSITION_COLLECTION:
                {
                    string metaclassName = kzuBinaryReadString(inputStream);

                    const Metaclass* metaclass = domain->getObjectFactory()->getMetaclass(metaclassName);
                    if (metaclass)
                    {
                        resource = metaclass->create<Resource>(domain, "");
                        resource->setNotLoaded();
                        resource->setKZB(kzuBinaryFileInfoGetDirectory(file), kzuBinaryFileInfoGetPath(file));
                        resource->load();
                    }
                    else
                    {
                        kzLogWarning(KZ_LOG_CATEGORY_GENERIC, ("Requested page transition collection type '{}' in file '{}' was not registered to engine.", metaclassName, string_view(name)));
                    }
                    break;
                }

                case KZU_BINARY_FILE_TYPE_EMPTY_NODE:
                case KZU_BINARY_FILE_TYPE_MESH_NODE:
                case KZU_BINARY_FILE_TYPE_CAMERA_NODE:
                case KZU_BINARY_FILE_TYPE_LIGHT_NODE:
                case KZU_BINARY_FILE_TYPE_LOD_SELECTOR_NODE:
                case KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE:
                case KZU_BINARY_FILE_TYPE_UI_COMPONENT_NODE_2D:
                case KZU_BINARY_FILE_TYPE_LAYER:
                case KZU_BINARY_FILE_TYPE_INSTANTIATOR_NODE:
                case KZU_BINARY_FILE_TYPE_SCENE:
                case KZU_BINARY_FILE_TYPE_PREFAB_OBJECT_PLACEHOLDER:
                case KZU_BINARY_FILE_TYPE_PREFAB_LAYER_PLACEHOLDER:
                case KZU_BINARY_FILE_TYPE_SCREEN:
                {
                    resource = kzuResourceManagerLoadPrefabTemplateNode_internal(domain, inputStream, file);

                    if (fileType == KZU_BINARY_FILE_TYPE_SCREEN)
                    {
                        PrefabTemplateNode* prefabNode = dynamic_cast<PrefabTemplateNode*>(resource.get());
                        kzAssert(prefabNode);
                        prefabNode->m_host = kzuBinaryDirectoryGetName(directory);
                    }

                    break;
                }
                case KZU_BINARY_FILE_TYPE_BINARY:
                {
                    resource = kzuResourceManagerLoadGenericFile_internal(domain, inputStream, file);
                    break;
                }

                default:
                {
                    kzAssertUnreachable();
                    break;
                }
            }

            result = kzcInputStreamDelete(inputStream);
            kzThrowIfError(result);

            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_PNG:
        case KZU_BINARY_FILE_TYPE_IMAGE_JPEG:
        case KZU_BINARY_FILE_TYPE_IMAGE_ETC:
        case KZU_BINARY_FILE_TYPE_IMAGE_PVRTC:
        case KZU_BINARY_FILE_TYPE_IMAGE_DXT:
        case KZU_BINARY_FILE_TYPE_IMAGE_ATC:
        case KZU_BINARY_FILE_TYPE_IMAGE_MIPMAP:
        case KZU_BINARY_FILE_TYPE_IMAGE_RAW_1D:
        case KZU_BINARY_FILE_TYPE_IMAGE_RAW_2D:
        case KZU_BINARY_FILE_TYPE_IMAGE_RAW_3D:
        case KZU_BINARY_FILE_TYPE_IMAGE_ASTC:
        case KZU_BINARY_FILE_TYPE_UTF8_TEXT:
        case KZU_BINARY_FILE_TYPE_ASCII_TEXT:
        case KZU_BINARY_FILE_TYPE_SHORTCUT:
        case KZU_BINARY_FILE_TYPE_MESSAGE_TYPE:
        case KZU_BINARY_FILE_TYPE_PROPERTY_TYPE:
        case KZU_BINARY_FILE_TYPE_PROJECT:
        case KZU_BINARY_FILE_TYPE_SPLINE:
        case KZU_BINARY_FILE_TYPE_LOCALIZATION_TABLE:
        case KZU_BINARY_FILE_TYPE_TEXT:
        {
            kzThrowLegacyErrorFormat(KZU_ERROR_WRONG_BINARY_FILE_TYPE,
                "Binary file type %d in file '%s' not supported by resource manager",
                (kzInt)fileType, name);
        }

        case KZU_BINARY_FILE_TYPE_INVALID:
        default:
        {
            kzThrowLegacyErrorFormat(KZU_ERROR_WRONG_BINARY_FILE_TYPE,
                "Unsupported binary file type %d in file '%s'", (kzInt)fileType, name);
        }
    }

    if (resource)
    {
        kzString path = kzuBinaryFileInfoGetPath(file);
        resource->setKZB(directory, path);
    }

    if (isShader)
    {
#ifdef KANZI_FEATURE_3D
        loadTask = make_shared<ShaderLoadTask>(domain, directory, file);
#endif
        kzAssert(!resource);
    }
    else if (isMesh)
    {
#ifdef KANZI_FEATURE_3D
        loadTask = make_shared<MeshLoadTask>(domain, directory, file);
#endif
        kzAssert(!resource);
    }
    else if (isTexture)
    {
#ifdef KANZI_FEATURE_3D
        loadTask = make_shared<TextureLoadTask>(domain, directory, file);
#endif
        kzAssert(!resource);
    }
    else
    {
        if (resource)
        {
            // Set loaded.
            resource->kzuResourceFinishLoading_private(&m_mainThreadContext);
        }
    }

    out_resource = resource;
    out_loadTask = loadTask;
}

}
