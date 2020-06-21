#ifndef RESOURCES_H
#define RESOURCES_H

class QString;

namespace Resources {

/**
 * Return the path to a directory called name in the resources directory
 */
QString findDir(const QString& name);

} // namespace Resources

#endif /* RESOURCES_H */
