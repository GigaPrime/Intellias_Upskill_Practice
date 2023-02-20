#include <string>
#include <vector>

class Processor
{
public:
    virtual void process() const = 0;
};

class ImageProcessor : public Processor
{
public:
    ImageProcessor(const std::string& path, const std::vector<std::string>& operations) : path(path), operations(operations) {};

    void process() const;

private:
    void resize(int width, int height);
    void crop(int x, int y, int width, int height);
    void blur(int radius);
    void watercolor(double radius, double xShift, double yShift);
    void cartoonize(double radius);

    std::string path;
    std::vector<std::string> operations;
};