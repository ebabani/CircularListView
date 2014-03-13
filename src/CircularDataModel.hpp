/*
 * CircularDataModel.hpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Ergin
 */

#ifndef CIRCULARDATAMODEL_HPP_
#define CIRCULARDATAMODEL_HPP_
#include <bb/cascades/QListDataModel>
#include <QtCore/QList>

#define LIST_LENGTH 100000

template <typename Item>
class CircularDataModel : public bb::cascades::DataModel {
public:
	CircularDataModel(const QList<Item>& other) : mListDataModel(other) {
		initSignals();
	}
	virtual ~CircularDataModel() {}

	virtual int childCount (const QVariantList &indexPath) {
		qDebug() << "childCount " << indexPath;
		if (indexPath.length() == 0) {
			int realCount = mListDataModel.childCount(indexPath);
			return LIST_LENGTH > realCount ? LIST_LENGTH : realCount;
		} else {
			return mListDataModel.childCount(indexPath);
		}
	}

	QVariant data(const QVariantList& indexPath) {
		if (indexPath.length() != 1) {
			return mListDataModel.data(indexPath);
		}
		int index = indexPath[0].toInt();
		int actualIndex = index % mListDataModel.size();

		QVariantList actualIndexPath;
		actualIndexPath << actualIndex;

		return mListDataModel.data(actualIndexPath);
	}

	bool hasChildren(const QVariantList &indexPath) {
		return mListDataModel.hasChildren(indexPath);
	}

	void append(const Item& newItem) {
		mListDataModel.append(newItem);
		emit itemsChanged(bb::cascades::DataModelChangeType::Update);
	}

	void initSignals() {
		QObject::connect(&mListDataModel, SIGNAL(itemAdded(QVariantList)),
				this, SIGNAL(itemAdded(QVariantList)));

		QObject::connect(&mListDataModel, SIGNAL(itemUpdated(QVariantList)),
				this, SIGNAL(itemUpdated(QVariantList)));

		QObject::connect(&mListDataModel, SIGNAL(itemRemoved(QVariantList)),
				this, SIGNAL(itemRemoved(QVariantList)));

		QObject::connect(&mListDataModel,
				SIGNAL(itemsChanged(bb::cascades::DataModelChangeType::Type,QSharedPointer<bb::cascades::DataModel::IndexMapper>)),
				this,
				SIGNAL(itemsChanged(bb::cascades::DataModelChangeType::Type,QSharedPointer<bb::cascades::DataModel::IndexMapper>)));
	}

private:
	bb::cascades::QListDataModel<Item> mListDataModel;
};

#endif /* CIRCULARDATAMODEL_HPP_ */
