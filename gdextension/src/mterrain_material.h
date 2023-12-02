#ifndef MTERRAINMATERIAL
#define MTERRAINMATERIAL


#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

#include "mconfig.h"

using namespace godot;

class MGrid;
class MImage;


class MTerrainMaterial : public Resource {
    GDCLASS(MTerrainMaterial,Resource);
    protected:
    static void _bind_methods();

    private:
    bool is_loaded=false;
    MGrid* grid=nullptr;
    Ref<Shader> shader;
    Ref<Shader> default_shader;
    Ref<Shader> show_region_shader;
    Vector<StringName> uniforms_names;
    int active_region=-1;
    // Uniform key->-1 is the defaulte uniform
    Dictionary uniforms; // Consist of key->Region Value->dictionary(Key->uniform_name value->Variant)
    PackedStringArray terrain_textures_names; // List of all texture uniforms for terrain texture
    PackedStringArray terrain_textures_added; // Textures uniforms which already added
    HashMap<String,int> terrain_textures_ids;
    HashMap<int,RID> materials;

    bool show_region = false;

    public:
    Vector<MImage*> all_images;
    Vector<MImage*> all_heightmap_images;
    void set_shader(Ref<Shader> input);
    Ref<Shader> get_shader();
    Ref<Shader> get_default_shader();
    Ref<Shader> get_currect_shader();
    void set_uniforms(Dictionary input);
    Dictionary get_uniforms();
    void set_clear_all(bool input);
    bool get_clear_all();
    void set_show_region(bool input);
    bool get_show_region();

    void update_uniforms_list();
    void _get_property_list(List<PropertyInfo> *p_list) const;
    bool _get(const StringName &p_name, Variant &r_ret) const;
    bool _set(const StringName &p_name, const Variant &p_value);
    void _shader_code_changed();
    void set_active_region(int input);
    int get_active_region();


    void set_grid(MGrid* g); // if grid is nullptr it means the terrain has been destroyed
    // Each time this is called it is going to generate a new material for that region
    RID get_material(int region_id); // OR region Index in grid
    void load_images();
    void clear();
    void add_terrain_image(String name); // The order of adding image will determine image ID in each grid creation
    void create_empty_terrain_image(String name,Image::Format format);
    int get_texture_id(const String& name);
    PackedStringArray get_textures_list();

    void set_uniform(RID mat,StringName uname,Variant value);
    void set_default_uniform(StringName uname,Variant value);
    void back_to_default_uniform(int region_id,StringName uname);
    void back_all_to_default_uniform(int region_id);
    void refresh_all_uniform();
    void clear_all_uniform();
    PackedStringArray get_reserved_uniforms() const;
};
#endif