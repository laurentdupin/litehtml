#include <html.h>

class DocumentContainer : public litehtml::document_container
{
public:
    DocumentContainer() = default;
    
    virtual litehtml::uint_ptr create_font(const char* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm)
    {
        return 1;
    }
    
    virtual void delete_font(litehtml::uint_ptr hFont)
    {
    
    }
    
    virtual int text_width(const char* text, litehtml::uint_ptr hFont)
    {
        return (int)strlen(text) * 15;
    }
    
    virtual void draw_text(litehtml::uint_ptr hdc, const char* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos)
    {
    
    }
    
    virtual int pt_to_px(int pt) const
    { 
        return 72 * pt / 96 ;
    }
    
    virtual int get_default_font_size() const
    {
        return 16;
    }
    
    virtual const char* get_default_font_name() const
    {
        return "Default";
    }
    
    virtual void draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker)
    {
    
    }
    
    virtual void load_image(const char* src, const char* baseurl, bool redraw_on_ready)
    {
    
    }
    
    virtual void get_image_size(const char *src, const char *baseurl, litehtml::size &sz) 
    {
    
    }
    
    virtual void draw_image(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const std::string &url, const std::string &base_url) 
    {
    
    }
    
    virtual void draw_solid_fill(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const litehtml::web_color &color)	
    {
    
    }
    
    virtual void draw_linear_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const litehtml::background_layer::linear_gradient &gradient) 
    {
    
    }
    
    virtual void draw_radial_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const litehtml::background_layer::radial_gradient &gradient) 
    {
    
    }
    
    virtual void draw_conic_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const litehtml::background_layer::conic_gradient &gradient) 
    {
    
    }
    
    virtual void draw_borders(litehtml::uint_ptr hdc, const litehtml::borders &borders, const litehtml::position &draw_pos, bool root) 
    {
    
    }
    
    virtual void set_caption(const char *caption) 
    {
    
    }
    
    virtual void set_base_url(const char *base_url) 
    {
    
    }
    
    virtual void link(const std::shared_ptr<litehtml::document> &doc, const litehtml::element::ptr &el) 
    {
    
    }
    
    virtual void on_anchor_click(const char *url, const litehtml::element::ptr &el) 
    {
    
    }
    
    virtual void on_mouse_event(const litehtml::element::ptr &el, litehtml::mouse_event event)	  
    {
    
    }
    
    virtual void set_cursor(const char *cursor) 
    {
    
    }
    
    virtual void transform_text(litehtml::string &text, litehtml::text_transform tt) 
    {
    
    }
    
    virtual void import_css(litehtml::string &text, const litehtml::string &url, litehtml::string &baseurl) 
    {
    
    }
    
    virtual void set_clip(const litehtml::position &pos, const litehtml::border_radiuses &bdr_radius) 
    {
    
    }
    
    virtual void del_clip() 
    {
    
    }
    
    virtual void get_client_rect(litehtml::position &client) const 
    {
        client.x = 0;
        client.y = 0;
        client.width = 1280;
        client.height = 720;
    }
    
    virtual litehtml::element::ptr create_element(const char *tag_name, const litehtml::string_map &attributes, const std::shared_ptr<litehtml::document> &doc) 
    {
        return 0;
    }
    
    virtual void get_media_features(litehtml::media_features &media) const 
    {
    
    }
    
    virtual void get_language(litehtml::string &language, litehtml::string &culture) const 
    {
    
    }
    
    virtual litehtml::string resolve_color(const litehtml::string &color) const 
    {
        return "black";
    }
    
    virtual void split_text(const char *text, const std::function<void(const char *)> &on_word, const std::function<void(const char *)> &on_space) 
    {
	    on_word(text);
    }
};

extern "C" 
{
    __declspec(dllexport) int GenerateDrawCalls(const char *page, const char* css) 
    {
        DocumentContainer container;
        auto doc = litehtml::document::createFromString(litehtml::estring(page), &container, litehtml::master_css, litehtml::estring(css));
        doc->render(10000);
		litehtml::position clip {0, 0, 1280, 720 };
        doc->draw(0, 0, 0, &clip);
        return 0;
    }
}