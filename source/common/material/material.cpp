#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our
{

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const
    {
        // TODO: (Req 7) Write this function
        pipelineState.setup(); // setup pipeline state
        shader->use();         // set the shader to be used
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        if (data.contains("pipelineState"))
        {
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint
    void TintedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        //  call the setup function of the parent class
        Material::setup();
        // set the value of "tint" uniform in the shader to the value of "tint" member variable
        shader->set("tint", tint); // the tinted material may be colors only without textures
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);
        if (!data.is_object())
            return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex"
    void TexturedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        TintedMaterial::setup();                       // call the setup function of the parent class
        shader->set("alphaThreshold", alphaThreshold); // set the value of "alphaThreshold" uniform in the shader to the value of "alphaThreshold" member variable
        if (texture)
        {
            texture->bind();       // bind the texture
            shader->set("tex", 0); // set the value of "tex" uniform in the shader to 0
        }
        if (sampler)
            sampler->bind(0); // bind the sampler to the texture unit 0
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json &data)
    {
        TintedMaterial::deserialize(data);
        if (!data.is_object())
            return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

    void LightMaterial::setup() const
    {
        Material::setup();
        // if (albedo != nullptr)
        // {
        //     glActiveTexture(GL_TEXTURE0);
        //     albedo->bind();
        //     sampler->bind(0);
        //     shader->set("material.albedo", 0);

        // }
        if (specular != nullptr)
        {
            glActiveTexture(GL_TEXTURE1);
            specular->bind();
            sampler->bind(1);
            shader->set("material.specular", 1);
        }
        if (emissive != nullptr)
        {
            glActiveTexture(GL_TEXTURE2);
            emissive->bind();
            sampler->bind(2);
            shader->set("material.emissive", 2);
        }
        if (roughness != nullptr)
        {
            glActiveTexture(GL_TEXTURE3);
            roughness->bind();
            sampler->bind(3);
            shader->set("material.roughness", 3);
        }
        if (ambient_occlusion != nullptr)
        {
            glActiveTexture(GL_TEXTURE4);
            ambient_occlusion->bind();
            sampler->bind(4);
            shader->set("material.ambient_occlusion", 4);
        }
        if (albedo != nullptr)
        {
            glActiveTexture(GL_TEXTURE0);
            albedo->bind();
            sampler->bind(0);
            shader->set("material.albedo", 0);
        }
    }
    void LightMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);
        if (!data.is_object())
            return;
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
        albedo = AssetLoader<Texture2D>::get(data.value("albedo", ""));
        specular = AssetLoader<Texture2D>::get(data.value("specular", ""));
        emissive = AssetLoader<Texture2D>::get(data.value("emissive", ""));
        roughness = AssetLoader<Texture2D>::get(data.value("roughness", ""));
        ambient_occlusion = AssetLoader<Texture2D>::get(data.value("ambient_occlusion", ""));
    }

}